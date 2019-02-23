#include<fftw3.h>

struct RealFFT {

    int length;
    double* in;
    fftw_complex *out;
    fftw_plan freak_quincys_evil_plan;
    

    RealFFT(size_t length) {
        this->length = length;
        this->in = (double*) fftw_malloc(sizeof(fftw_complex) * length);
        this->out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * length);

        this->freak_quincys_evil_plan = fftw_plan_dft_r2c_1d(length, this->in, this->out, FFTW_ESTIMATE);
    }
    
    ~RealFFT() { 
        fftw_free(this->in);
        fftw_free(this->out);
        fftw_destroy_plan(this->freak_quincys_evil_plan);
    }

    void rfft_execute_freak_quincys_evil_plan() {
        fftw_execute(this->freak_quincys_evil_plan);
    }
};
