#include "wave_form.h"

WaveForm::WaveForm(int size, WaveTypes waveType) : size(size), 
wType(waveType), angles(size), waveOutput(size) {
    this->generateWave();
}

WaveForm::~WaveForm() {
    angles.clear();
    waveOutput.clear();
}

int WaveForm::get_size() const {
    return angles.size();
}

WaveTypes WaveForm::get_wave_type() const {
    return wType;
}

std::vector<double> WaveForm::get_angles() const {
    return angles;
}

std::vector<double> WaveForm::get_waveOutput() const {
    return waveOutput;
}

void WaveForm::generateWave() {
    auto angleDelta = 2*M_PI / (size-1);
    auto currentAngle = 0.0;

    for(int i = 0; i < size; i++) {
        waveOutput[i] = sin(currentAngle);
        angles[i] = currentAngle;

        currentAngle += angleDelta;
    }
}