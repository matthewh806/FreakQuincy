#ifndef VCO_HPP
#define VCO_HPP

#include "engine/Oscillator.hpp"
#include "engine/WaveForm.hpp"

namespace engine {

    class VCO : public Oscillator {
        public:
            VCO();
            ~VCO();            
    };
}

#endif