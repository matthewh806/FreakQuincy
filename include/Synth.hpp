#ifndef Synth_hpp
#define Synth_hpp

// This will eventually be a subtractive synth (haven't read that section of the book yet...)
#include "wave_form.h"
#include "ADSR.hpp"
#include "WaveFormSignalHandler.hpp"
#include <memory>

class Synth {
    public:
        Synth();
        ~Synth();

        std::shared_ptr<WaveFormSignalHandler> getWaveFormSignalHandler();

        // TODO: Get the note...?
        void noteOn();
        void noteOff();
        double tick();

    private:
        // TODO: Check if these still actually have any benefit being shared.
        std::shared_ptr<WaveForm> m_waveForm;
        std::shared_ptr<WaveFormSignalHandler> m_waveFormSignalHandler;

        ADSR *m_adsr;

};

#endif