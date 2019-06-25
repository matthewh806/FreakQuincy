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
    WaveForm(float sampleRate);
    ~WaveForm();

    int get_size() const;
    
    WaveTypes get_wave_type() const;
    void set_waveType(WaveTypes w_type);

    void set_sampleRate(float rate);

    std::vector<double> get_angles() const;
    std::vector<double> get_waveOutput() const;

    void generateWaves(float frequency);

private:
    float sampleRate;
    int tableSize;
    WaveTypes wType;
    std::vector<double> angles;
    std::vector<double> sineWaveTable;
    std::vector<double> sqrWaveTable;

    std::vector<double> sineWave;
    std::vector<double> sqrWave;

    void generateWaveTables();
    void generateSineWaveTable();
    void generateSquareWaveTable();
};

#endif