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
    
}

void MainWindow::setupPlottingWindow() {

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    customPlot = new QCustomPlot(centralWidget);
    customPlot->setObjectName(QStringLiteral("TEST PLOT!"));

    verticalLayout->addWidget(customPlot);

    this->setCentralWidget(centralWidget);

   /*
    * Calculations
    */
    std::unique_ptr<WaveForm> p_wave( new WaveForm(N, WaveTypes::SINE) );
    QVector<double> angles_vec = QVector<double>::fromStdVector(p_wave->get_angles());
    QVector<double> values_vec = QVector<double>::fromStdVector(p_wave->get_waveOutput());
    
    std::unique_ptr<RealFFT> p_rFFT ( new RealFFT(N ));
    p_rFFT->rfft_execute_freak_quincys_evil_plan();

    customPlot->addGraph();
    customPlot->graph(0)->setData(angles_vec, values_vec);
    customPlot->xAxis->setLabel("angle");
    customPlot->yAxis->setLabel("sin(angle)");

    customPlot->graph(0)->rescaleAxes();
}
