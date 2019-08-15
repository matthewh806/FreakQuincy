#ifndef LFO_HPP
#define LFO_HPP

#include "engine/Oscillator.hpp"
#include "engine/WaveForm.hpp"

namespace engine {
    enum class Destinations {
        PITCH,
        AMP,
        FILTER,
        RESONANCE,
        NONE
    };

    // TODO: This should inherit from something else maybe? Modulator?
    class LFO : public Oscillator {

        public: 
            LFO();
            ~LFO();

            void notePressed(float freq, bool legato) override;
            void setFrequency(float freq) override;

            Destinations getDestination() { return m_destination; }
            void setDestination(Destinations destination) { this->m_destination = destination; }


        private:
            const float MIN_FREQUENCY = 0.0625;
            const float MAX_FREQUENCY = 100.0;

            double m_rate; // env time units per tick

            double m_state; // between 0 and 1
            bool m_free;

            Destinations m_destination = Destinations::NONE;
    };
}

#endif