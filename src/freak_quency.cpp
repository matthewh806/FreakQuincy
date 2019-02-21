#include <iostream>
#include <fstream>
#include<fftw3.h>

#include "math.h"

int N = 1024;

void generate_wave(double *waveTable, float phase) {

    auto angleDelta = M_PI_2 / N-1;
    auto currentAngle = 0.0;

    for(int i = 0; i < N; i++) {
        waveTable[i] = sin(currentAngle);
        currentAngle += angleDelta;
    }
}

int main(int argc, const char * argv[]) {
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
   std::fstream outFile("output.txt");

   /*
    * Calculations
    */
    generate_wave(in, 0.0f);

    if(outFile.is_open()) {
        for(int i = 0; i < N; i++) {
            outFile << in[i] << ", ";
        }

        outFile.close();
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
