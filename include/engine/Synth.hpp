#ifndef SYNTH_HPP
#define SYNTH_HPP

// This will eventually be a subtractive synth (haven't read that section of the book yet...)
#include <memory>
#include "engine/VCO.hpp"
#include "engine/LFO.hpp"
#include "engine/ADSR.hpp"

namespace engine {
    class Synth {
        public:
            Synth();
            ~Synth();

            void setOscFrequency(double freq);
            void setOscType(WaveTypes type);

            float getAttack();
            void setAttack(float t);
            
            float getDecay();
            void setDecay(float t);

            float getSustain();
            void setSustain(float t);

            float getRelease();
            void setRelease(float t);

            bool legatoPlay();

            void noteOn(float freq=0, bool legatoEvent = false);
            void noteOff(bool legatoEvent);
            double tick();

        private:
            // TODO: Check if these still actually have any benefit being shared.
            std::unique_ptr<VCO> m_VCO;
            std::unique_ptr<LFO> m_LFO;
            std::unique_ptr<ADSR> m_adsr;
    };
}

#endif