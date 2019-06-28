#include "wave_form.h"
#include "AudioSettings.hpp"

// TODO: RESIZE ARRAY IF BUFFER SIZE CHANGES!
WaveForm::WaveForm() : angles(AudioSettings::getbufferSize()), 
sineWaveTable(AudioSettings::getbufferSize()), sqrWaveTable(AudioSettings::getbufferSize()), sineWave(AudioSettings::getbufferSize()), sqrWave(AudioSettings::getbufferSize()){
    phase = 0.0;

    generateWaveTables();
    generateWaves(1);
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

double WaveForm::get_inst_waveOutput(float frequency) {
    increment = (AudioSettings::getbufferSize() * frequency) / AudioSettings::getSampleRate();
    
    int index0 = (int)phase;
    int index1 = (index0 == AudioSettings::getbufferSize() - 1) ? 0 : index0 + 1;

    auto t = phase - (float)index0;
    
    phase = fmod(phase + increment, AudioSettings::getbufferSize());

    return (1-t) * wType == SINE ? sineWaveTable[index0] : sqrWaveTable[index0] + t * wType == SINE ? sineWaveTable[index1] : sqrWaveTable[index1];
}

void WaveForm::generateWaves(float frequency) {
    // Generate wave at sampling freq. with specified oscillator frequency

    float increment = (AudioSettings::getbufferSize() * frequency) / AudioSettings::getSampleRate();
    float angleIncrement = 2*M_PI * frequency / AudioSettings::getSampleRate();

    float phase = 0;
    float angle = 0;
    for(int i = 0; i < AudioSettings::getbufferSize(); i++) {
        // Lerp between values to get output: (1-t) * v0 + t * v1;
        int index0 = (int)phase;
        int index1 = (index0 == AudioSettings::getbufferSize() - 1) ? 0 : index0 + 1;

        auto t = phase - (float)index0;
        
        phase = fmod(phase + increment, AudioSettings::getbufferSize());

        sineWave[i] = (1-t) * sineWaveTable[index0] + t * sineWaveTable[index1];
        sqrWave[i] = (1-t) * sqrWaveTable[index0] + t * sqrWaveTable[index1];

        angle += angleIncrement;
        angles[i] = angle;
    }
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