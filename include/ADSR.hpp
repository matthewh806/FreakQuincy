#ifndef ADSR_HPP
#define ADSR_HPP

#include <vector>

class ADSR {
    enum STAGE {
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE,
        DONE,
        NUM_STAGES
    };

    public:
        ADSR();

        // TODO: Implement param values in constructor? (e.g. attack lvl may not be 1)
        ADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime);
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

        void NotePressed();
        void NoteReleased();

        // This is just the same as tick for now.
        double getEnvelopeOutput();

        friend std::ostream& operator<<(std::ostream& out, const ADSR& adsr);
    private:
        STAGE m_stage = DONE;
        double m_state;
        double m_rate; // env time units per tick
        double m_curParamVal; // current parameter value
        double m_prevParamVal; // Parameter value at start of current stage

        // The following vectors follow this pattern: A, De, S, R, Do (De = Decay, Do = Done)
        std::vector<float> m_stageTimes;  // Time when each stage ends S,D = inf
        std::vector<float> m_paramValues; // Target param. value of stage De = S, R=Do = 0
};

#endif