#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include "math.h"

enum class WaveTypes {
    SINE
};

class WaveForm {
public:
    WaveForm(int size, WaveTypes waveType);
    ~WaveForm();

    int get_size() const;
    WaveTypes get_wave_type() const;
    std::vector<double> get_angles() const;
    std::vector<double> get_waveOutput() const;

    void generateWave(float frequency = 1.0, float phase = 0.0);

private:
    int size;
    WaveTypes wType;
    std::vector<double> angles;
    std::vector<double> waveOutput;
};

#endif