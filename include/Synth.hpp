#ifndef Synth_hpp
#define Synth_hpp

// This will eventually be a subtractive synth (haven't read that section of the book yet...)
#include "wave_form.h"
#include "ADSR.hpp"
#include <memory>

class Synth {
    public:
        Synth();
        ~Synth();

        void setOscFrequency(double freq);
        void setOscType(WaveTypes type);

        // TODO: Get the note...?
        void noteOn();
        void noteOff();
        double tick();

    private:
        // TODO: Check if these still actually have any benefit being shared.
        std::shared_ptr<WaveForm> m_waveForm;
        ADSR *m_adsr;
};

#endif