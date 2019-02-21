#include <iostream>
#include<fftw3.h>

int N = 1024;

int main(int argc, const char * argv[]) {
    std::cout << "Hello Freak Quency!" << std::endl;

    int input_size = N;
    int output_size = (input_size / 2 + 1 );

    double* in;
    fftw_complex *out;
    fftw_plan freak_quincys_evil_plan;

    in = (double*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N); 
    freak_quincys_evil_plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

    fftw_execute(freak_quincys_evil_plan);
    
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(freak_quincys_evil_plan);

    return 0;
}
