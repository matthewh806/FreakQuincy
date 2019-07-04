#include <iostream>
#include "Synth.hpp"

Synth::Synth() {
    m_waveForm = std::make_shared<WaveForm>();
    m_waveFormSignalHandler = std::make_shared<WaveFormSignalHandler>(m_waveForm);
    m_adsr = new ADSR(1, 0.2, 0.1, 0.2); // TODO: better way of handling defaults than this.

    std::cout << *m_adsr << std::endl;
}

Synth::~Synth() {
    // TODO
}

std::shared_ptr<WaveFormSignalHandler> Synth::getWaveFormSignalHandler() {
    return m_waveFormSignalHandler;
}

void Synth::noteOn() {
    m_adsr->NotePressed();
}

void Synth::noteOff() {
    m_adsr->NoteReleased();
}

double Synth::tick() {
    return m_waveForm->get_waveOutput() * m_adsr->getEnvelopeOutput();
}