#include <iostream>
#include <cmath>
#include "engine/Spectrum.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    double defaultWindow(int index, size_t length) {
        return 1;
    }

    Spectrum::Spectrum(double* input, std::function<double (int, size_t)> windowFunc) : in(input) 
    {
        // Apply window function
        if(windowFunc == nullptr) {
            windowFunc = defaultWindow;
        }

        double windowedInput[AudioSettings::getbufferSize()];
        for(int i = 0; i < AudioSettings::getbufferSize(); i++) {
            windowedInput[i] = windowFunc(i, AudioSettings::getbufferSize()) * input[i];
        }

        fft = new RealFFT(AudioSettings::getbufferSize(), windowedInput);

        frequencies.reserve(AudioSettings::getbufferSize()/2 + 1);
        power_spectrum.reserve(AudioSettings::getbufferSize()/2 + 1);
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
        for(int i = 0; i < AudioSettings::getbufferSize() / 2; i++) {        
            frequencies.push_back((float)i / AudioSettings::getbufferSize() * AudioSettings::getSampleRate());

            // This calculates amplitude
            power_spectrum.push_back(std::sqrt( fft->out[i][0]*fft->out[i][0] + fft->out[i][1]*fft->out[i][1]));
        }
    }
}
