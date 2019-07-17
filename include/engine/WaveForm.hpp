#ifndef WAVEFORM_HPP
#define WAVEFORM_HPP

#include <vector>
#include "math.h"

namespace engine {
    enum WaveTypes {
        SINE = 0,
        TRIANGLE,
        SAWTOOTH,
        SQUARE
    };

    class WaveForm {
    public:
        WaveForm();
        ~WaveForm();
        
        WaveTypes get_wave_type() const;
        void set_waveType(WaveTypes w_type);

        void NotePressed(float freq);
        void NoteReleased();

        void setFrequency(float freq);

        double get_waveOutput();
        void generateWaves(float frequency);

    private:
        double phase;
        float increment;

        float freq;

        WaveTypes wType;
        std::vector<double> sineWaveTable;
        std::vector<double> triWaveTable;
        std::vector<double> sawWaveTable;
        std::vector<double> sqrWaveTable;

        void generateWaveTables();
        void generateSineWaveTable();
        void generateTriWaveTable();
        void generateSawWaveTable();
        void generateSquareWaveTable();
    };
}

#endif