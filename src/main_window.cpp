#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include<fftw3.h>
#include "main_window.h"
#include "wave_form.h"

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

    customPlot->addGraph();
    customPlot->graph(0)->setData(angles_vec, values_vec);
    customPlot->xAxis->setLabel("angle");
    customPlot->yAxis->setLabel("sin(angle)");

    customPlot->graph(0)->rescaleAxes();
}

int main_needs_renaming() {
    std::cout << "Hello Freak Quency!" << std::endl;

    /*
    * Fourier variables
    */
    int input_size = N;
    int output_size = (input_size / 2 + 1 );

    double* in;
    fftw_complex *out;
    fftw_plan freak_quincys_evil_plan;

    in = (double*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    freak_quincys_evil_plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

    /*
    * Outputting variables
    */
   double* angles = new double[N];
   std::fstream outFile("output.txt");
   std::fstream anglesOut("angles.txt");

    fftw_execute(freak_quincys_evil_plan);
    

    /*
    * Output
    */


    /*
    * Cleanup
    */ 
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(freak_quincys_evil_plan);

    return 0;
}
