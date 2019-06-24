#include "wave_form.h"

WaveForm::WaveForm(float sampleRate) : sampleRate(sampleRate), angles(sampleRate), 
sineWave(sampleRate), sqrWave(sampleRate) {
    generateWaves();
}

WaveForm::~WaveForm() {
    angles.clear();
    sineWave.clear();
    sqrWave.clear();
}

int WaveForm::get_size() const {
    return angles.size();
}

WaveTypes WaveForm::get_wave_type() const {
    return wType;
}

void WaveForm::set_waveType(WaveTypes w_type) {
    wType = w_type;
}

std::vector<double> WaveForm::get_angles() const {
    return angles;
}

std::vector<double> WaveForm::get_waveOutput() const {
    if(wType == SINE) {
        return sineWave;
    } else {
        return sqrWave;
    }
}

void WaveForm::generateWaves(float frequency, float phase) {
    generateSineWave(frequency, phase);
    generateSquareWave(frequency, phase);
}

void WaveForm::generateSineWave(float frequency, float phase) {
    auto angleDelta = 2*M_PI / (sampleRate - 1) * frequency;
    auto currentAngle = 0.0;

    for(int i = 0; i < sampleRate; i++) {
        sineWave[i] = sin(currentAngle + phase);
        angles[i] = currentAngle;

        currentAngle += angleDelta;
    }
}

void WaveForm::generateSquareWave(float frequency, float phase) {
    auto angleDelta = 2*M_PI / (sampleRate - 1) * frequency;
    auto currentAngle = 0.0;

    for(int i = 0; i < sampleRate; i++) {
        sqrWave[i] = sin(currentAngle + phase) >= 0.0 ? 1.0 : -1.0;
        angles[i] = currentAngle;

        currentAngle += angleDelta;
    }
}