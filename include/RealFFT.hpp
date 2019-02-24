#include<fftw3.h>

struct RealFFT {

    int length;
    double* in;
    fftw_complex *out;
    fftw_plan freak_quincys_evil_plan;
    

    RealFFT(size_t length, double* input) {
        this->length = length;
        this->in = input;
        this->out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (length/2 + 1));

        this->freak_quincys_evil_plan = fftw_plan_dft_r2c_1d(length, this->in, this->out, FFTW_ESTIMATE);
    }
    
    ~RealFFT() { 
        // TODO: this was causing a segmentation fault because it used elsewhere. FIX PROPERLY
        // fftw_free(this->in);
        fftw_free(this->out);
        fftw_destroy_plan(this->freak_quincys_evil_plan);
    }

    void execute_freak_quincys_evil_plan() {
        fftw_execute(this->freak_quincys_evil_plan);
    }
};
