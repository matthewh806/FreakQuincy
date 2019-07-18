#include <iostream>
#include "engine/Synth.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    Synth::Synth() {
        m_waveForm = std::make_shared<WaveForm>();
        m_adsr = new ADSR(1, 0.2, 0.1, 0.2); // TODO: better way of handling defaults than this.

        std::cout << *m_adsr << std::endl;
    }

    Synth::~Synth() {
        // TODO
    }

    bool Synth::legatoPlay() {
        return AudioSettings::isLegatoEnabled();
    }

    void Synth::noteOn(float freq, bool legatoEvent) {
        m_waveForm->NotePressed(freq);
        m_adsr->notePressed(legatoPlay() && legatoEvent);
    }

    void Synth::noteOff(bool legatoEvent) {
        m_waveForm->NoteReleased();
        m_adsr->noteReleased(legatoPlay() && legatoEvent);
    }

    void Synth::setOscFrequency(double freq) {
        m_waveForm->setFrequency(freq);
    }

    void Synth::setOscType(WaveTypes type) {
        m_waveForm->set_waveType(type);
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

    double Synth::tick() {
        return m_waveForm->get_waveOutput() * m_adsr->getEnvelopeOutput();
    }
}