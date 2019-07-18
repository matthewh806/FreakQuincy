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

    double Synth::tick() {
        return m_waveForm->get_waveOutput() * m_adsr->getEnvelopeOutput();
    }
}