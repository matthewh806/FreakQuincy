#ifndef SPECTRUM_HPP
#define SPECTRUM_HPP

#include "dep/RealFFT.hpp"
#include <vector>
#include <functional>

class Spectrum {
public:
    Spectrum(double* input, std::function<double (int, size_t)> windowFunc = nullptr);
    ~Spectrum();

    std::vector<double> get_frequencyRange();
    std::vector<double> get_powerSpectrum();

    void generatePowerSpectrum();
    
private:
    RealFFT *fft;
    double* in;

    std::vector<double> frequencies;
    std::vector<double> power_spectrum;
};

#endif