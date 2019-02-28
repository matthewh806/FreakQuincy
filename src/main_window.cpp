#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "main_window.h"
#include "spectrum.hpp"
#include "wave_form.h"

int N = 1024;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    std::cout << "Hello Freak Quency!" << std::endl;

    setupPlottingWindow();
}

MainWindow::~MainWindow() {
    delete centralWidget;
    delete verticalLayout;
    delete waveformPlot;
    delete spectrumPlot;
}

void MainWindow::setupPlottingWindow() {

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    waveformPlot = new QCustomPlot(centralWidget);
    waveformPlot->setObjectName(QStringLiteral("Waveform Plot"));

    spectrumPlot = new QCustomPlot(centralWidget);
    spectrumPlot->setObjectName(QStringLiteral("Spectrum Plot"));

    verticalLayout->addWidget(waveformPlot);
    verticalLayout->addWidget(spectrumPlot);

    this->setCentralWidget(centralWidget);

   /*
    * Calculations
    */
    std::unique_ptr<WaveForm> p_wave( new WaveForm(N, WaveTypes::SINE) );
    QVector<double> angles_vec = QVector<double>::fromStdVector(p_wave->get_angles());
    QVector<double> values_vec = QVector<double>::fromStdVector(p_wave->get_waveOutput());
    
    Spectrum* s = new Spectrum(N, p_wave->get_waveOutput().data());
    s->generatePowerSpectrum();

    QVector<double> frequencies = QVector<double>::fromStdVector(s->get_frequencyRange());
    QVector<double> power_spec = QVector<double>::fromStdVector(s->get_powerSpectrum());

    std::cout << "------------------_*****************" << std::endl;
    std::cout << "size: " << frequencies.size() << std::endl;
    for(int i = 0; i < frequencies.size(); i++) {
        std::cout << "(x, y): " << "(" << frequencies[i] << ", " << power_spec[i] << ")" << std::endl;
    }

    // TODO: Plot magnitude against frequency;
    // TODO: Maybe it should be a log plot?
    waveformPlot->addGraph();
    waveformPlot->graph(0)->setData(angles_vec, values_vec);
    waveformPlot->xAxis->setLabel("angle");
    waveformPlot->yAxis->setLabel("sin(angle)");
    waveformPlot->graph(0)->rescaleAxes();

    spectrumPlot->addGraph();
    spectrumPlot->graph(0)->setData(frequencies, power_spec);
    spectrumPlot->xAxis->setLabel("frequency");
    spectrumPlot->yAxis->setLabel("level");
    waveformPlot->graph(0)->rescaleAxes();
}
