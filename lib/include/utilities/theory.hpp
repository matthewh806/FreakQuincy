#ifndef THEORY_HPP
#define THEORY_HPP

#include <math.h>

namespace utilities {
    namespace constants {
        static const float FREQ_C4 = 261.6256f;
        static const float FREQ_A4 = 440.0000f;
        static const float TWELFTH_POWER_OF_TWO = 1.0594630944f; // semi-tone interval
    }

    static float centShiftToFreq(float baseFreq, double centShift) {
        return pow(2, centShift / (float)12000) * baseFreq;
    }

    static float semitoneShiftToFreq(float baseFreq, double semitoneShift) {
        return pow(2, semitoneShift / 12.0) * baseFreq;  
    }

    static float midiNoteToFreq(uint8_t midiNote) {
        // TODO: Check midi note value is between 0 - 127

        // TODO: Reference frequency? Default is A4 = 440Hz, m_A4 = 69
        return pow(2, (float)(midiNote - 69)/12.0)*constants::FREQ_A4;
    };
}

#endif