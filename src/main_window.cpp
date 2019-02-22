#include <iostream>
#include <fstream>
#include <vector>
#include<fftw3.h>
#include "math.h"
#include "main_window.h"

int N = 1024;

void generate_wave(std::vector<double> &angles, std::vector<double> &waveTable) {
    auto angleDelta = 2*M_PI / (N-1);
    auto currentAngle = 0.0;

    for(int i = 0; i < N; i++) {
        waveTable[i] = sin(currentAngle);
        angles[i] = currentAngle;

        currentAngle += angleDelta;
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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

    std::vector<double> angles(N);
    std::vector<double> values(N);

    generate_wave(angles, values);

    QVector<double> angles_vec = QVector<double>::fromStdVector(angles);
    QVector<double> values_vec = QVector<double>::fromStdVector(values);

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

   /*
    * Calculations
    */
    // generate_wave(angles, in);

    // TODO: Obviously this is a rubbish way of writing data to the system.
    if(outFile.is_open()) {
        for(int i = 0; i < N; i++) {
            outFile << in[i] << ", ";
        }

        outFile.close();
    }

    if(anglesOut.is_open()) {
        for(int i = 0; i < N; i++) {
            anglesOut << angles[i] << ", ";
        }

        anglesOut.close();
    }

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
