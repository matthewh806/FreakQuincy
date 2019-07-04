#include <iostream>
#include "Synth.hpp"

Synth::Synth() {
    m_waveForm = std::make_shared<WaveForm>();
    m_adsr = new ADSR(1, 0.2, 0.1, 0.2); // TODO: better way of handling defaults than this.

    std::cout << *m_adsr << std::endl;
}

Synth::~Synth() {
    // TODO
}

void Synth::noteOn() {
    m_adsr->NotePressed();
}

void Synth::noteOff() {
    m_adsr->NoteReleased();
}

void Synth::setOscFrequency(double freq) {
    m_waveForm->setFrequency(freq);
}

void Synth::setOscType(WaveTypes type) {
    m_waveForm->set_waveType(type);
}

double Synth::tick() {
    return m_waveForm->get_waveOutput() * m_adsr->getEnvelopeOutput();
}