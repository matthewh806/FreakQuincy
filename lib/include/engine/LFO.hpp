#ifndef LFO_HPP
#define LFO_HPP

#include "engine/Oscillator.hpp"
#include "engine/Modulator.hpp"

namespace engine {
    // TODO: This should inherit from something else maybe? Modulator?
    class LFO : public Oscillator, public Modulator {

        public: 
            LFO(WaveTypes type, double freq, double depth, bool bypass);
            ~LFO();

            double tick(double input = 0) override;

            void notePressed(float freq, bool legato) override;
            void setFrequency(float freq) override;

        private:
            const float MIN_FREQUENCY = 0.0625;
            const float MAX_FREQUENCY = 100.0;

            double m_rate; // env time units per tick

            double m_state; // between 0 and 1
            bool m_free;
    };
}

#endif