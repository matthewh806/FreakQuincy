#ifndef SPECTRUM_H
#define SPECTRUM_H

#include "RealFFT.hpp"
#include <vector>
#include <functional>

class Spectrum {
public:
    Spectrum(size_t length, double* input, std::function<double (int, size_t)> windowFunc = nullptr);
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