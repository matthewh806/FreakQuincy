#include "wave_form.h"

WaveForm::WaveForm(float sampleRate) : tableSize(1000), sampleRate(sampleRate), angles(tableSize), 
sineWaveTable(tableSize), sqrWaveTable(tableSize), sineWave(tableSize), sqrWave(tableSize){
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

void WaveForm::set_sampleRate(float rate) {
    sampleRate = rate;
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

void WaveForm::generateWaves(float frequency) {
    // Generate wave at sampling freq. with specified oscillator frequency

    float increment = (tableSize * frequency) / sampleRate;
    float angleIncrement = 2*M_PI * frequency / sampleRate;

    float phase = 0;
    float angle = 0;
    for(int i = 0; i < tableSize; i++) {
        // Lerp between values to get output: (1-t) * v0 + t * v1;
        int index0 = (int)phase;
        int index1 = (index0 == tableSize - 1) ? 0 : index0 + 1;

        auto t = phase - (float)index0;
        
        phase = fmod(phase + increment, tableSize);

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
    auto angleDelta = 2*M_PI / (tableSize - 1);
    auto currentAngle = 0.0;

    for(int i = 0; i < tableSize; i++) {
        sineWaveTable[i] = sin(currentAngle);
        currentAngle += angleDelta;
    }
}

void WaveForm::generateSquareWaveTable() {
    auto angleDelta = 2*M_PI / (tableSize - 1);
    auto currentAngle = 0.0;

    for(int i = 0; i < tableSize; i++) {
        sqrWaveTable[i] = sin(currentAngle) >= 0.0 ? 1.0 : -1.0;
        currentAngle += angleDelta;
    }
}