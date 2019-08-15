#include <iostream>
#include "engine/Synth.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    Synth::Synth() {
        m_VCO = std::unique_ptr<VCO>(new VCO());
        m_LFO = std::unique_ptr<LFO>(new LFO());
        m_VCA = std::unique_ptr<VCA>(new VCA());

        m_LFO->setDestination(Destinations::AMP);
        m_LFO->setFrequency(20);
        m_LFO->setWaveType(WaveTypes::SINE);
    }

    Synth::~Synth() {
        // TODO
    }

    bool Synth::legatoPlay() {
        return AudioSettings::isLegatoEnabled();
    }

    void Synth::noteOn(float freq, bool legatoEvent) {
        bool legato = legatoPlay() && legatoEvent;

        m_VCO->notePressed(freq, legato);
        m_LFO->notePressed(freq, legato);
        m_VCA->notePressed(freq, legato);
    }

    void Synth::noteOff(bool legatoEvent) {
        bool legato = legatoPlay() && legatoEvent;

        m_VCO->noteReleased(legato);
        m_VCA->noteReleased(legato);
        m_LFO->noteReleased(legato);
    }

    void Synth::setOscFrequency(double freq) {
        m_VCO->setFrequency(freq);
    }

    void Synth::setOscType(WaveTypes type) {
        m_VCO->setWaveType(type);
    }

    float Synth::getAttack() {
        return m_VCA->getEnvelope()->getAttackTime();
    }

    void Synth::setAttack(float t) {
        m_VCA->getEnvelope()->setAttackTime(t);
    }

    float Synth::getDecay() {
        return m_VCA->getEnvelope()->getDecayTime();
    }

    void Synth::setDecay(float t) {
        m_VCA->getEnvelope()->setDecayTime(t);
    }

    float Synth::getSustain() {
        return m_VCA->getEnvelope()->getSustainLevel();
    }

    void Synth::setSustain(float t) {
        m_VCA->getEnvelope()->setSustainLevel(t);
    }

    float Synth::getRelease() {
        return m_VCA->getEnvelope()->getReleaseTime();
    }

    void Synth::setRelease(float t) {
        m_VCA->getEnvelope()->setReleaseTime(t);
    }

    void Synth::setLfoOscType(WaveTypes type) {
        m_LFO->setWaveType(type);
    }

    void Synth::setLfoFrequency(double freq) {
        m_LFO->setFrequency((float)freq);
    }

    void Synth::setLfoDestination(Destinations dest) {
        m_LFO->setDestination(dest);
    }

    double Synth::tick() {
        return m_VCO->tick() * m_VCA->tick() * m_LFO->tick();
    }
}