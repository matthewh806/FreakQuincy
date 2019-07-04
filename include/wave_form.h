#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include "math.h"

enum WaveTypes {
    SINE = 0,
    SQUARE
};

class WaveForm {
public:
    WaveForm();
    ~WaveForm();
    
    WaveTypes get_wave_type() const;
    void set_waveType(WaveTypes w_type);

    void setFrequency(float freq);

    double get_waveOutput();

    void generateWaves(float frequency);

private:
    double phase;
    float increment;

    float freq;

    WaveTypes wType;
    std::vector<double> sineWaveTable;
    std::vector<double> sqrWaveTable;

    void generateWaveTables();
    void generateSineWaveTable();
    void generateSquareWaveTable();
};

#endif