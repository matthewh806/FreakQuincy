#ifndef SYNTH_HPP
#define SYNTH_HPP

// This will eventually be a subtractive synth (haven't read that section of the book yet...)
#include <memory>
#include "engine/WaveForm.hpp"
#include "engine/ADSR.hpp"

namespace engine {
    class Synth {
        public:
            Synth();
            ~Synth();

            void setOscFrequency(double freq);
            void setOscType(WaveTypes type);

            void noteOn(float freq=0);
            void noteOff();
            double tick();

        private:
            // TODO: Check if these still actually have any benefit being shared.
            std::shared_ptr<WaveForm> m_waveForm;
            ADSR *m_adsr;
    };
}

#endif