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

            WaveTypes getLfoOscType() { return m_LFO->getWaveType(); }
            void setLfoOscType(WaveTypes type);

            float getLfoFrequency() { return m_LFO->getFrequency(); };
            void setLfoFrequency(double freq);

            Destinations getLfoDestination() { return m_LFO->getDestination(); }
            void setLfoDestination(Destinations dest);

            bool legatoPlay();

            void noteOn(float freq=0, bool legatoEvent = false);
            void noteOff(bool legatoEvent);

            double tick();

        private:
            std::unique_ptr<VCO> m_VCO;
            std::unique_ptr<LFO> m_LFO;
            std::unique_ptr<ADSR> m_adsr;
    };
}

#endif