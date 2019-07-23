#ifndef LFO_HPP
#define LFO_HPP

#include "engine/WaveForm.hpp"

namespace engine {
    enum class Destinations {
        PITCH,
        VOLUME,
        NOT_SET
    };

    class LFO : public WaveForm {

        public: 
            LFO();
            ~LFO();

            void NotePressed(float freq, bool legato) override;
            void setFrequency(float freq) override;
            
            Destinations getDestination() { return m_destination; }
            void setDestination(Destinations destination) { this->m_destination = destination; }

            // double getOutput() override;

        private:
            const float MIN_FREQUENCY = 0.0625;
            const float MAX_FREQUENCY = 100.0;

            double m_rate; // env time units per tick

            double m_state; // between 0 and 1
            bool m_free;

            Destinations m_destination = Destinations::NOT_SET;
    };
}

#endif