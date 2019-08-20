#ifndef SYNTH_HPP
#define SYNTH_HPP

// This will eventually be a subtractive synth (haven't read that section of the book yet...)
#include <memory>
#include <map>

#include "engine/VCO.hpp"
#include "engine/Mixer.hpp"
#include "engine/LFO.hpp"
#include "engine/VCA.hpp"

namespace engine {
    class Synth {
        public:
            Synth();
            ~Synth();

            void setOscFrequency(int idx, double freq);
            void setOscType(int idx, WaveTypes type);

            float getAttack();
            void setAttack(float t);
            
            float getDecay();
            void setDecay(float t);

            float getSustain();
            void setSustain(float t);

            float getRelease();
            void setRelease(float t);

            WaveTypes getLfoOscType(int idx);
            void setLfoOscType(int idx, WaveTypes type);

            float getLfoFrequency(int idx);
            void setLfoFrequency(int idx, double freq);

            float getLfoDepth(int idx);
            void setLfoDepth(int idx, double depth);

            bool getLfoBypassState(int idx);
            void setLfoBypass(int idx, bool bypass);

            Destinations getLfoDestination(int idx);
            void setLfoDestination(int idx, Destinations dest);

            bool legatoPlay();

            void noteOn(float freq=0, bool legatoEvent = false);
            void noteOff(bool legatoEvent);

            double tick();

        private:
            std::map<int, std::unique_ptr<VCO>> m_VCOs;
            std::map<int, std::unique_ptr<LFO>> m_LFOs;
            std::unique_ptr<VCA> m_VCA;
            std::unique_ptr<Mixer> m_mixer;
    };
}

#endif