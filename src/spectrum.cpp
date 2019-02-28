#include <iostream>
#include <cmath>
#include "spectrum.hpp"

Spectrum::Spectrum(size_t length, double* input) : length(length), in(input) 
{
    fft = new RealFFT(length, in);

    frequencies.reserve(length/2 + 1);
    power_spectrum.reserve(length/2 + 1);
}

Spectrum::~Spectrum() {
    // TODO: DUH!
}

std::vector<double> Spectrum::get_frequencyRange() {
    return frequencies;
}

std::vector<double> Spectrum::get_powerSpectrum() {
    return power_spectrum;
}

void Spectrum::generatePowerSpectrum() {
    fft->execute_freak_quincys_evil_plan();

    // TODO: What happens when N is even?
    for(int i = 0; i < length / 2; i++) {
        std::cout << " (re, im) : " << "(" << fft->out[i][0] << ", " << fft->out[i][1] << ")" << std::endl;
        
        frequencies.push_back(i);
        power_spectrum.push_back(std::sqrt( fft->out[i][0]*fft->out[i][0] + fft->out[i][1]*fft->out[i][1]));
    }
}