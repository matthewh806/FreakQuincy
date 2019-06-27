#include <iostream>
#include <cmath>
#include "spectrum.hpp"

double defaultWindow(int index, size_t length) {
    return 1;
}

Spectrum::Spectrum(size_t length, double* input, std::function<double (int, size_t)> windowFunc) : length(length), in(input) 
{
    // Apply window function
    if(windowFunc == nullptr) {
        windowFunc = defaultWindow;
    }

    double windowedInput[length];
    for(int i = 0; i < length; i++) {
        windowedInput[i] = windowFunc(i, length) * input[i];
    }

    fft = new RealFFT(length, windowedInput);

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

void Spectrum::generatePowerSpectrum(float sample_rate) {
    fft->execute_freak_quincys_evil_plan();

    // TODO: What happens when N is even?
    for(int i = 0; i < length / 2; i++) {        
        frequencies.push_back((float)i / length * sample_rate);

        // This calculates amplitude
        power_spectrum.push_back(std::sqrt( fft->out[i][0]*fft->out[i][0] + fft->out[i][1]*fft->out[i][1]));
    }
}