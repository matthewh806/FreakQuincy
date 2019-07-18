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
            std::shared_ptr<WaveForm> m_waveForm;
            ADSR *m_adsr;
    };
}

#endif