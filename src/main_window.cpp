#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "main_window.h"
#include "wave_form.h"
#include "RealFFT.hpp"

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
    
    std::unique_ptr<RealFFT> p_rFFT ( new RealFFT(N, p_wave->get_waveOutput().data()));
    p_rFFT->execute_freak_quincys_evil_plan();

    QVector<double> power_spec(N/2 + 1);
    QVector<double> frequencies(N/2 +1);
    // TODO: Convert to power spectrum. (magnitude)
    // TODO: What happens when N is even?
    for(int i = 0; i < N / 2; i++) {
        std::cout << " (re, im) : " << "(" << p_rFFT->out[i][0] << ", " << p_rFFT->out[i][1] << ")" << std::endl;
        
        frequencies[i] = i;
        power_spec[i] = std::sqrt( p_rFFT->out[i][0] * p_rFFT->out[i][0] + p_rFFT->out[i][1]*p_rFFT->out[i][1]);
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
