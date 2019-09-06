#ifndef VCA_HPP
#define VCA_HPP

#include "engine/ModuleBase.hpp"
#include "engine/Modulatable.hpp"
#include "engine/AbstractEnvelope.hpp"

namespace engine {
    class VCA : public ModuleBase, public Modulatable {
        public:
            VCA();
            ~VCA();

            void setGain(double g) { this->gain = g; }
            double getGain() { return gain; }

            AbstractEnvelope* getEnvelope() { return envelope.get(); }

            void notePressed(float freq, bool legato) override { envelope->notePressed(freq, legato); };
            void noteReleased(bool legato) override { envelope->noteReleased(legato); };
            double tick(double input = 0) override;

        private:
            double gain;
            std::unique_ptr<AbstractEnvelope> envelope;
    };
}

#endif