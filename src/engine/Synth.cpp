#include <iostream>
#include "engine/Synth.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    Synth::Synth() {
        m_VCO = std::unique_ptr<VCO>(new VCO());
        m_LFO = std::unique_ptr<LFO>(new LFO());
        // TODO: better way of handling defaults than this.
        m_adsr = std::unique_ptr<ADSR>(new ADSR(1, 0.2, 0.1, 0.2));

        m_LFO->setDestination(Destinations::VOLUME);
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
        m_adsr->notePressed(freq, legato);
    }

    void Synth::noteOff(bool legatoEvent) {
        bool legato = legatoPlay() && legatoEvent;

        m_VCO->noteReleased(legato);
        m_adsr->noteReleased(legato);
        m_LFO->noteReleased(legato);
    }

    void Synth::setOscFrequency(double freq) {
        m_VCO->setFrequency(freq);
    }

    void Synth::setOscType(WaveTypes type) {
        m_VCO->setWaveType(type);
    }

    float Synth::getAttack() {
        return m_adsr->getAttackTime();
    }

    void Synth::setAttack(float t) {
        m_adsr->setAttackTime(t);
    }

    float Synth::getDecay() {
        return m_adsr->getDecayTime();
    }

    void Synth::setDecay(float t) {
        m_adsr->setDecayTime(t);
    }

    float Synth::getSustain() {
        return m_adsr->getSustainLevel();
    }

    void Synth::setSustain(float t) {
        m_adsr->setSustainLevel(t);
    }

    float Synth::getRelease() {
        return m_adsr->getReleaseTime();
    }

    void Synth::setRelease(float t) {
        m_adsr->setReleaseTime(t);
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
        return m_VCO->tick() * m_adsr->tick() * m_LFO->tick();
    }
}