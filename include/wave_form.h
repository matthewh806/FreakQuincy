#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include "math.h"

enum WaveTypes {
    SINE,
    SQUARE
};

class WaveForm {
public:
    WaveForm(float sampleRate);
    ~WaveForm();

    int get_size() const;
    
    WaveTypes get_wave_type() const;
    void set_waveType(WaveTypes w_type);

    std::vector<double> get_angles() const;
    std::vector<double> get_waveOutput() const;

    void generateWaves(float frequency = 1.0, float phase = 0.0);

private:
    float sampleRate;
    WaveTypes wType;
    std::vector<double> angles;
    std::vector<double> sineWave;
    std::vector<double> sqrWave;

    void generateSineWave(float frequency, float phase);
    void generateSquareWave(float frequency, float phase);
};

#endif