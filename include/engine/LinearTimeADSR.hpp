#ifndef LINEARTIMEADSR_HPP
#define LINEARTIMEADSR_HPP

#include <vector>

#include "engine/AbstractEnvelope.hpp"

namespace engine {
    class LinearTimeADSR : public AbstractEnvelope {
        public:
            LinearTimeADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime, double depth, bool bypass)
            : AbstractEnvelope(attackTime, decayTime, sustainLevel, releaseTime, depth, bypass) {};

            ~LinearTimeADSR() {};
 
            void notePressed(float freq, bool legato) override;
            void noteReleased(bool legato) override;

            double tick() override;
    };
}

#endif