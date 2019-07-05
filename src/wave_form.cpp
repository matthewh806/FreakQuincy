#include "WaveForm.hpp"
#include "AudioSettings.hpp"

// TODO: RESIZE ARRAY IF BUFFER SIZE CHANGES!
WaveForm::WaveForm() : sineWaveTable(AudioSettings::getbufferSize()), sqrWaveTable(AudioSettings::getbufferSize()) {
    phase = 0.0;

    generateWaveTables();
}

WaveForm::~WaveForm() {
}

WaveTypes WaveForm::get_wave_type() const {
    return wType;
}

void WaveForm::setFrequency(float freq) {
    this->freq = freq;
}

void WaveForm::set_waveType(WaveTypes w_type) {
    wType = w_type;
}

double WaveForm::get_waveOutput() {
    increment = (AudioSettings::getbufferSize() * freq) / AudioSettings::getSampleRate();
    
    int index0 = (int)phase;
    int index1 = (index0 == AudioSettings::getbufferSize() - 1) ? 0 : index0 + 1;

    auto t = phase - (float)index0;
    
    phase = fmod(phase + increment, AudioSettings::getbufferSize());

    return (1-t) * wType == SINE ? sineWaveTable[index0] : sqrWaveTable[index0] + t * wType == SINE ? sineWaveTable[index1] : sqrWaveTable[index1];
}

void WaveForm::generateWaveTables() {
    generateSineWaveTable();
    generateSquareWaveTable();
}

void WaveForm::generateSineWaveTable() {
    auto angleDelta = 2*M_PI / (AudioSettings::getbufferSize() - 1);
    auto currentAngle = 0.0;

    for(int i = 0; i < AudioSettings::getbufferSize(); i++) {
        sineWaveTable[i] = sin(currentAngle);
        currentAngle += angleDelta;
    }
}

void WaveForm::generateSquareWaveTable() {
    auto angleDelta = 2*M_PI / (AudioSettings::getbufferSize() - 1);
    auto currentAngle = 0.0;

    for(int i = 0; i < AudioSettings::getbufferSize(); i++) {
        sqrWaveTable[i] = sin(currentAngle) >= 0.0 ? 1.0 : -1.0;
        currentAngle += angleDelta;
    }
}