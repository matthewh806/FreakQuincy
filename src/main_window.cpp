#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "main_window.h"
#include "spectrum.hpp"
#include <math.h>

float sampleRate = 40000;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    std::cout << "Hello Freak Quency!" << std::endl;

    p_wave = std::unique_ptr<WaveForm>( new WaveForm(sampleRate) );
    setupMainWindow();
}

MainWindow::~MainWindow() {
    delete waveformPlot;
    delete spectrumPlot;
    delete verticalLayout;
    delete centralWidget;
}

void MainWindow::sampleRateChanged(double rate) {
    sampleRate = rate;
}

void MainWindow::frequencyChanged(double freq) {
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
    sampleRateSpinBox->setRange(0, 40000);
    sampleRateSpinBox->setSingleStep(1000);
    sampleRateSpinBox->setValue(40000);
    connect(sampleRateSpinBox, SIGNAL(valueChanged(double)), this, SLOT(sampleRateChanged(float)));

    QComboBox *waveformSelector = new QComboBox;
    waveformSelector->insertItem(waveformSelector->count(), "Sine", WaveTypes::SINE);
    waveformSelector->insertItem(waveformSelector->count(), "Square", WaveTypes::SQUARE);
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
    plotData();
}

void MainWindow::setupPlottingWindow() {
    // TODO: Remove any existing plots if they exist - Replotting doesn't work atm...

    // TODO: Plot magnitude against frequency;
    // TODO: Maybe it should be a log plot?
    waveformPlot->addGraph();
    waveformPlot->xAxis->setLabel("angle");
    waveformPlot->yAxis->setLabel("sin(angle)");
    
    spectrumPlot->addGraph();
    spectrumPlot->xAxis->setLabel("frequency");
    spectrumPlot->yAxis->setLabel("level");
}

void MainWindow::plotData() {
    QVector<double> angles_vec = QVector<double>::fromStdVector(p_wave->get_angles());
    QVector<double> values_vec = QVector<double>::fromStdVector(p_wave->get_waveOutput());
    
    for(int i = 0; i < values_vec.size(); i++) {
        std::cout << "(x, y): " << "(" << angles_vec[i] << ", " << values_vec[i] << ")" << std::endl;
    }

    Spectrum* s = new Spectrum((int)sampleRate, p_wave->get_waveOutput().data());
    s->generatePowerSpectrum(sampleRate);

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
