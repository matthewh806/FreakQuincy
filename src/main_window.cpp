#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <math.h>
#include <numeric>
#include "main_window.h"
#include "spectrum.hpp"
#include "wave_form.h"
#include "AudioSettings.hpp"

// TODO: Separate class for UI to core engine...!
// TODO: Button to start / stop audio stream.
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    x_axis = QVector<double>(AudioSettings::getbufferSize());
    std::iota(x_axis.begin(), x_axis.end(), 1);

    setupMainWindow();
}

MainWindow::~MainWindow() {
    delete waveformPlot;
    delete spectrumPlot;
    delete verticalLayout;
    delete centralWidget;

    delete noteButton;
}

void MainWindow::sampleRateChanged(int rate) {
    AudioSettings::setSampleRate(rate);
}

void MainWindow::setupMainWindow() {
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    QLabel *waveformLabel = new QLabel(tr("Parameters"));
    QGroupBox *waveFormGroup = new QGroupBox(tr("Parameters"));

    QLabel *sampleRateLabel = new QLabel(tr("Sample Rate"));
    sampleRateSpinBox = new QSpinBox;
    sampleRateSpinBox->setRange(1000, 44100);
    sampleRateSpinBox->setSingleStep(1000);
    sampleRateSpinBox->setValue(AudioSettings::getSampleRate());
    connect(sampleRateSpinBox, SIGNAL(valueChanged(int)), this, SLOT(sampleRateChanged(int)));

    waveformSelector = new QComboBox;
    waveformSelector->insertItem(waveformSelector->count(), "Sine", WaveTypes::SINE);
    waveformSelector->insertItem(waveformSelector->count(), "Square", WaveTypes::SQUARE);
    waveformSelector->setCurrentIndex(-1);

    QLabel *frequencyLabel = new QLabel(tr("Frequency"));
    frequencySpinBox = new QDoubleSpinBox;
    frequencySpinBox->setRange(0, 25000);
    frequencySpinBox->setSingleStep(1.0);
    frequencySpinBox->setValue(1.0);

    QLabel *phaseLabel = new QLabel(tr("Phase"));
    phaseSpinBox = new QDoubleSpinBox;
    phaseSpinBox->setRange(-360, 360);
    phaseSpinBox->setSingleStep(1.0);
    phaseSpinBox->setValue(0.0);

    noteButton = new QPushButton("Note", this);

    QVBoxLayout *waveFormSpinBoxLayout = new QVBoxLayout();
    waveFormSpinBoxLayout->addWidget(sampleRateLabel);
    waveFormSpinBoxLayout->addWidget(sampleRateSpinBox);
    waveFormSpinBoxLayout->addWidget(waveformLabel);
    waveFormSpinBoxLayout->addWidget(waveformSelector);
    waveFormSpinBoxLayout->addWidget(frequencyLabel);
    waveFormSpinBoxLayout->addWidget(frequencySpinBox);
    waveFormSpinBoxLayout->addWidget(phaseLabel);
    waveFormSpinBoxLayout->addWidget(phaseSpinBox);
    waveFormSpinBoxLayout->addWidget(noteButton);
    waveFormGroup->setLayout(waveFormSpinBoxLayout);

    waveformPlot = new QCustomPlot(centralWidget);
    waveformPlot->setObjectName(QStringLiteral("Waveform Plot"));

    spectrumPlot = new QCustomPlot(centralWidget);
    spectrumPlot->setObjectName(QStringLiteral("Spectrum Plot"));

    verticalLayout->addWidget(waveFormGroup);
    verticalLayout->addWidget(waveformPlot);
    verticalLayout->addWidget(spectrumPlot);

    this->setCentralWidget(centralWidget);

    setupPlottingWindow();
    waveformSelector->setCurrentIndex(WaveTypes::SINE);
}

void MainWindow::setupPlottingWindow() {
    // TODO: Remove any existing plots if they exist - Replotting doesn't work atm...

    // TODO: Plot magnitude against frequency;
    // TODO: Maybe it should be a log plot?
    waveformPlot->addGraph();
    waveformPlot->xAxis->setLabel("angle");
    waveformPlot->yAxis->setLabel("Amplitude");
    
    spectrumPlot->addGraph();
    spectrumPlot->xAxis->setLabel("frequency");
    spectrumPlot->yAxis->setLabel("Amplitude");
}

double hammingWindow(int index, size_t length) {
    double alpha = 0.53836;

    return alpha - (1-alpha) * cos(2 * M_PI * index / (length - 1));
}

void MainWindow::plotData(std::vector<double> amplitudes) {
    if(amplitudes.size() != x_axis.size()) {
        x_axis.resize(amplitudes.size());
        std::iota(x_axis.begin(), x_axis.end(), 1);
    }

    QVector<double> values_vec = QVector<double>::fromStdVector(amplitudes);

    // TODO: Maybe don't calculate this in the graphics thread...?
    Spectrum* s = new Spectrum(amplitudes.data(), hammingWindow);
    s->generatePowerSpectrum();

    std::vector<double> ps = s->get_powerSpectrum();

    // TODO: This modifies vector - not really desirable
    std::for_each(ps.begin(), ps.end(), [](double &n) { n = 20 * log10(n);});

    QVector<double> frequencies = QVector<double>::fromStdVector(s->get_frequencyRange());
    QVector<double> power_spec = QVector<double>::fromStdVector(ps);

    waveformPlot->graph(0)->data()->clear();
    waveformPlot->graph(0)->setData(x_axis, values_vec);
    waveformPlot->graph(0)->rescaleAxes();
    waveformPlot->replot();

    spectrumPlot->graph(0)->data()->clear();
    spectrumPlot->graph(0)->setData(frequencies, power_spec);
    spectrumPlot->graph(0)->rescaleAxes();
    spectrumPlot->replot();
}
