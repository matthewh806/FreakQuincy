#ifndef ADSR_hpp
#define ADSR_hpp

#include <vector>

class ADSR {
    enum STATE {
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE,
        DONE
    };

    public:
        ADSR();

        // TODO: Implement param values in constructor? (e.g. attack lvl may not be 1)
        ADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime);
        ~ADSR();

        // This is just the same as tick for now.
        double getEnvelopeOutput();

        float getAttackTime();
        void setAttackTime(float t);

        float getDecayTime();
        void setDecayTime(float t);

        float getSustainLevel();
        void setSustainLevel(float l);

        float getReleaseTime();
        void setReleaseTime(float t);

    private:
        STATE m_state = DONE;

        // The following vectors follow this pattern: A, De, S, R, Do (De = Decay, Do = Done)
        std::vector<float> m_stateTimes;  // Time when each stage ends S,D = inf
        std::vector<float> m_paramValues; // Target param. value of stage De = S, R=Do = 0
};

#endif