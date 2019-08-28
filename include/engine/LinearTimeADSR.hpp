#ifndef LINEARTIMEADSR_HPP
#define LINEARTIMEADSR_HPP

#include "engine/AbstractEnvelope.hpp"

namespace engine {
    class LinearTimeADSR : public AbstractEnvelope {
        public:
            LinearTimeADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime, double depth, bool bypass)
            : AbstractEnvelope(attackTime, decayTime, sustainLevel, releaseTime, depth, bypass) {
                m_state = 0.0;
            };

            ~LinearTimeADSR() {};
 
            double tick() override;
    };
}

#endif