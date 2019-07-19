#ifndef SPECTRUM_HPP
#define SPECTRUM_HPP

#include "dep/RealFFT.hpp"
#include <vector>
#include <functional>

namespace engine {
    class Spectrum {
    public:
        Spectrum();
        ~Spectrum();

        std::vector<double> get_frequencyRange();
        std::vector<double> get_powerSpectrum();

        void generatePowerSpectrum(double* input, std::function<double (int, size_t)> windowFunc);
        
    private:
        std::vector<double> frequencies;
        std::vector<double> power_spectrum;
    };
}

#endif