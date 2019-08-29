#ifndef EXPONENTIALTIMEADSR_HPP
#define EXPONENTIALTIMEADSR_HPP

#include "engine/AbstractEnvelope.hpp"

namespace engine {
    class ExponentialTimeADSR : public AbstractEnvelope {
        
        public:
            ExponentialTimeADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime, double depth, bool bypass)
            : AbstractEnvelope(attackTime, decayTime, sustainLevel, releaseTime, depth, bypass) 
            {
                eps = 0.001;
            }

            ~ExponentialTimeADSR() {};
 
            double tick(double input = 0) override;

        protected:
            void goToStage(STAGE stage) override;

        private:
            double eps; // to prevent zeno's paradox (repeated multiplications will just tend to zero)
            double gamma; // multiplier for exp multiplication see: http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/

            void calculateMultiplier(double startLevel, double endLevel, double length);
    };
}

#endif