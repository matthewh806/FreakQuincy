#ifndef VCA_HPP
#define VCA_HPP

#include "engine/Module.hpp"
#include "engine/ADSR.hpp"

namespace engine {
    class VCA : public Module {
        public:
            VCA();
            ~VCA();

            void setGain(double g) { this->gain = g; }
            double getGain() { return gain; }

            ADSR* getEnvelope() { return envelope.get(); }

            void notePressed(float freq, bool legato) override { envelope->notePressed(freq, legato); };
            void noteReleased(bool legato) override { envelope->noteReleased(legato); };
            double tick() override;

        private:
            double gain;
            std::unique_ptr<ADSR> envelope;
    };
}

#endif