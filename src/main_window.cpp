#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <math.h>
#include "main_window.h"
#include "spectrum.hpp"
#include "AudioSettings.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    std::cout << "Hello Freak Quency!" << std::endl;

    AudioSettings::setSampleRate(40000);
    AudioSettings::setChannels(2);
    AudioSettings::setBufferSize(1000);

    p_wave = std::unique_ptr<WaveForm>( new WaveForm() );

    setupMainWindow();
}

MainWindow::~MainWindow() {
    delete waveformPlot;
    delete spectrumPlot;
    delete verticalLayout;
    delete centralWidget;
}

void MainWindow::sampleRateChanged(double rate) {
    AudioSettings::setSampleRate((float)rate);

    p_wave->generateWaves(curFreq);
    plotData();
}

void MainWindow::frequencyChanged(double freq) {
    curFreq = (float)freq;
    p_wave->generateWaves(freq);
    plotData();
}

void MainWindow::phaseChanged(double phase) {
    p_wave->generateWaves(1.0);
    plotData();
}

void MainWindow::waveformChanged(int index) {
    p_wave->set_waveType((WaveTypes)index);
    plotData();
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
    QDoubleSpinBox *sampleRateSpinBox = new QDoubleSpinBox;
    sampleRateSpinBox->setRange(1000, 40000);
    sampleRateSpinBox->setSingleStep(1000);
    sampleRateSpinBox->setValue(AudioSettings::getSampleRate());
    connect(sampleRateSpinBox, SIGNAL(valueChanged(double)), this, SLOT(sampleRateChanged(double)));

    QComboBox *waveformSelector = new QComboBox;
    waveformSelector->insertItem(waveformSelector->count(), "Sine", WaveTypes::SINE);
    waveformSelector->insertItem(waveformSelector->count(), "Square", WaveTypes::SQUARE);
    waveformSelector->setCurrentIndex(-1);
    connect(waveformSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(waveformChanged(int)));

    QLabel *frequencyLabel = new QLabel(tr("Frequency"));
    QDoubleSpinBox *frequencySpinBox = new QDoubleSpinBox;
    frequencySpinBox->setRange(0, 2000);
    frequencySpinBox->setSingleStep(1.0);
    frequencySpinBox->setValue(1.0);
    connect(frequencySpinBox, SIGNAL(valueChanged(double)), this, SLOT(frequencyChanged(double)));

    QLabel *phaseLabel = new QLabel(tr("Phase"));
    QDoubleSpinBox *phaseSpinBox = new QDoubleSpinBox;
    phaseSpinBox->setRange(-360, 360);
    phaseSpinBox->setSingleStep(1.0);
    phaseSpinBox->setValue(0.0);
    connect(phaseSpinBox, SIGNAL(valueChanged(double)), this, SLOT(phaseChanged(double)));

    QVBoxLayout *waveFormSpinBoxLayout = new QVBoxLayout();
    waveFormSpinBoxLayout->addWidget(sampleRateLabel);
    waveFormSpinBoxLayout->addWidget(sampleRateSpinBox);
    waveFormSpinBoxLayout->addWidget(waveformLabel);
    waveFormSpinBoxLayout->addWidget(waveformSelector);
    waveFormSpinBoxLayout->addWidget(frequencyLabel);
    waveFormSpinBoxLayout->addWidget(frequencySpinBox);
    waveFormSpinBoxLayout->addWidget(phaseLabel);
    waveFormSpinBoxLayout->addWidget(phaseSpinBox);
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

void MainWindow::plotData() {
    QVector<double> angles_vec = QVector<double>::fromStdVector(p_wave->get_angles());
    QVector<double> values_vec = QVector<double>::fromStdVector(p_wave->get_waveOutput());

    Spectrum* s = new Spectrum(p_wave->get_waveOutput().data(), hammingWindow);
    s->generatePowerSpectrum();

    std::vector<double> ps = s->get_powerSpectrum();

    // TODO: This modifies vector - not really desirable
    std::for_each(ps.begin(), ps.end(), [](double &n) { n = 20 * log10(n);});

    QVector<double> frequencies = QVector<double>::fromStdVector(s->get_frequencyRange());
    QVector<double> power_spec = QVector<double>::fromStdVector(ps);

    waveformPlot->graph(0)->data()->clear();
    waveformPlot->graph(0)->setData(angles_vec, values_vec);
    waveformPlot->graph(0)->rescaleAxes();
    waveformPlot->replot();

    spectrumPlot->graph(0)->data()->clear();
    spectrumPlot->graph(0)->setData(frequencies, power_spec);
    spectrumPlot->graph(0)->rescaleAxes();
    spectrumPlot->replot();
}
