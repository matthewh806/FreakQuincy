#ifndef SPECTRUM_H
#define SPECTRUM_H

#include "RealFFT.hpp"
#include <vector>

class Spectrum {
public:
    Spectrum(size_t length, double* input);
    ~Spectrum();

    std::vector<double> get_frequencyRange();
    std::vector<double> get_powerSpectrum();

    void generatePowerSpectrum(float sample_rate);
    
private:
    RealFFT *fft;
    int length;
    double* in;

    std::vector<double> frequencies;
    std::vector<double> power_spectrum;
};

#endif