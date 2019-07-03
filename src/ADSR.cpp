#include "ADSR.hpp"
ADSR::ADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime) {
    m_stateTimes = std::vector<float> { 
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
}

ADSR::~ADSR() {
    // TODO: Cleanup!
}

double ADSR::getEnvelopeOutput() {
    return 1.0;
}

float ADSR::getAttackTime() {
    return m_stateTimes[ATTACK];
}

void ADSR::setAttackTime(float t) {
    m_stateTimes[ATTACK] = t;
}

float ADSR::getDecayTime() {
    return m_stateTimes[DECAY];
}

void ADSR::setDecayTime(float t) {
    m_stateTimes[DECAY] = t;
}

float ADSR::getSustainLevel() {
    return m_paramValues[SUSTAIN];
}

void ADSR::setSustainLevel(float l) {
    m_paramValues[SUSTAIN] = l;
}

float ADSR::getReleaseTime() {
    return m_paramValues[RELEASE];
}

void ADSR::setReleaseTime(float t) {
    m_paramValues[RELEASE] = t;
}