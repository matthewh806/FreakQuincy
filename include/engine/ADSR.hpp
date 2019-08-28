#ifndef ADSR_HPP
#define ADSR_HPP

#include <vector>
#include "engine/Modulator.hpp"

namespace engine {
    class ADSR : public Modulator {
        enum STAGE {
            RAMP_DOWN,
            ATTACK,
            DECAY,
            SUSTAIN,
            RELEASE,
            DONE,
            NUM_STAGES
        };

        public:
            ADSR();

            ADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime, double depth, bool bypass);
            ~ADSR();
 
            double getRate();

            float getAttackTime();
            void setAttackTime(float t);

            float getDecayTime();
            void setDecayTime(float t);

            float getSustainLevel();
            void setSustainLevel(float l);

            float getReleaseTime();
            void setReleaseTime(float t);

            void notePressed(float freq, bool legato) override;
            void noteReleased(bool legato) override;

            // This is just the same as tick for now.
            double tick() override;

            friend std::ostream& operator<<(std::ostream& out, const ADSR& adsr);
        private:
            STAGE m_stage = DONE;
            double m_state;
            double m_rate; // env time units per tick
            double m_curParamVal; // current parameter value
            double m_prevParamVal; // Parameter value at start of current stage

            // The following vectors follow this pattern: RAMP, A, De, S, R, Do (De = Decay, Do = Done)
            std::vector<float> m_stageTimes;  // Time when each stage ends S,D = inf
            std::vector<float> m_paramValues; // Target param. value of stage De = S, RAMP=R=Do= 0
    };
}

#endif