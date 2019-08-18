#ifndef VCO_HPP
#define VCO_HPP

#include "engine/ModuleBase.hpp"
#include "engine/Modulatable.hpp"
#include "engine/Oscillator.hpp"
#include "engine/WaveForm.hpp"

namespace engine {

    class VCO : public Oscillator, public ModuleBase, public Modulatable {
        public:
            VCO(WaveTypes wType, double freq) : Oscillator(wType, freq) {}
            ~VCO() {};

            void notePressed(float freq, bool legato) override { m_waveForm->setFrequency(freq); };
            double tick() override;
    };
}

#endif