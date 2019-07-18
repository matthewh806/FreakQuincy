#include <iostream>
#include "engine/ADSR.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {

    ADSR::ADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime) {
        m_stageTimes = std::vector<float> { 
            attackTime, 
            decayTime, 
            std::numeric_limits<float>::infinity(),
            releaseTime,
            std::numeric_limits<float>::infinity()
        };

        m_paramValues = std::vector<float> {
            1,
            sustainLevel,
            sustainLevel,
            0,
            0
        };

        // TODO: Is this the correct way of setting rate...?
        m_rate = 1.0 / AudioSettings::getSampleRate();
        m_state = 0.0;
        m_curParamVal = 0.0;
        m_prevParamVal = 0.0;
    }

    ADSR::~ADSR() {
        // TODO: Cleanup!
    }

    double ADSR::getRate() {
        return m_rate;
    }

    float ADSR::getAttackTime() {
        return m_stageTimes[ATTACK];
    }

    void ADSR::setAttackTime(float t) {
        m_stageTimes[ATTACK] = t;
    }

    float ADSR::getDecayTime() {
        return m_stageTimes[DECAY];
    }

    void ADSR::setDecayTime(float t) {
        m_stageTimes[DECAY] = t;
    }

    float ADSR::getSustainLevel() {
        return m_paramValues[SUSTAIN];
    }

    void ADSR::setSustainLevel(float l) {
        m_paramValues[SUSTAIN] = l;
    }

    float ADSR::getReleaseTime() {
        return m_stageTimes[RELEASE];
    }

    void ADSR::setReleaseTime(float t) {
        m_stageTimes[RELEASE] = t;
    }

    void ADSR::notePressed(bool legato) {
        if(legato)
            return;

        m_stage = ATTACK;
        m_state = 0.0;
        m_curParamVal = 0.0;
        m_prevParamVal = 0.0;
    }

    void ADSR::noteReleased(bool legato) {
        if(m_stage >= RELEASE || legato)
            return;
        
        m_stage = RELEASE;
        m_state = 0.0;
        m_prevParamVal = m_curParamVal;
    }

    double ADSR::getEnvelopeOutput() {
        m_state += m_rate;

        if(m_state >= m_stageTimes[m_stage]) {
            m_state -= m_stageTimes[m_stage];
            m_prevParamVal = m_curParamVal;
            
            m_stage = static_cast<STAGE>((m_stage + 1) % NUM_STAGES);
        }

        double gamma = m_state / m_stageTimes[m_stage];
        m_curParamVal = (1-gamma) * m_prevParamVal + gamma * m_paramValues[m_stage];
        return m_curParamVal;
    }

    std::ostream& operator<<(std::ostream& out, const ADSR& adsr) {
        out << "ADSR: " << adsr.m_rate << ", " << adsr.m_stageTimes[0] << ", " << adsr.m_stageTimes[1] << ", " << adsr.m_stageTimes[3];
        return out;
    }
}