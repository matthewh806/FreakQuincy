#include <iostream>

#include "engine/WaveForm.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    
    // TODO: RESIZE ARRAY IF BUFFER SIZE CHANGES!

    // TODO: Check when this initialization occurs...?
    std::vector<double> WaveForm::sineWaveTable(AudioSettings::getbufferSize());
    std::vector<double> WaveForm::sqrWaveTable(AudioSettings::getbufferSize());
    std::vector<double> WaveForm::triWaveTable(AudioSettings::getbufferSize()); 
    std::vector<double> WaveForm::sawWaveTable(AudioSettings::getbufferSize());

    bool WaveForm::tablesInitialized = false;

    WaveForm::WaveForm() {
        phase = 0.0;

        if(!tablesInitialized) {
            generateWaveTables();
            tablesInitialized = true;
        }
    }

    WaveForm::~WaveForm() {
    }

    WaveTypes WaveForm::getWaveType() const {
        return wType;
    }

    void WaveForm::setWaveType(WaveTypes w_type) {
        wType = w_type;
    }
    
    void WaveForm::setFrequency(float freq) {
        this->m_freq = freq;
    }

    double WaveForm::getOutput(float freqOffset) {
        increment = (AudioSettings::getbufferSize() * (m_freq + freqOffset)) / AudioSettings::getSampleRate();
        
        int index0 = (int)phase;
        int index1 = (index0 == AudioSettings::getbufferSize() - 1) ? 0 : index0 + 1;

        auto t = phase - (float)index0;
        
        phase = fmod(phase + increment, AudioSettings::getbufferSize());

        std::vector<double> *waveTable = nullptr;

        switch(wType) {
            case(SINE):
                waveTable = &sineWaveTable;
                break;
            case(TRIANGLE):
                waveTable = &triWaveTable;
                break;
            case(SAWTOOTH):
                waveTable = &sawWaveTable;
                break;
            case(SQUARE):
                waveTable = &sqrWaveTable;
                break;
            case(NOT_SET):
                waveTable = nullptr;
        }

        if(!waveTable)
            return 1.0;

        return (1-t) * waveTable->at(index0) + t * waveTable->at(index1);
    }

    void WaveForm::generateWaveTables() {
        generateSineWaveTable();
        generateTriWaveTable();
        generateSawWaveTable();
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

    void WaveForm::generateTriWaveTable() {
        float stepDelta = 1.0 / (AudioSettings::getbufferSize() - 1);
        float t = 0.0;

        // Assuming period = 1 here
        for(int i = 0; i < AudioSettings::getbufferSize(); i++) {
            triWaveTable[i] = 2 * abs(2 * (t - floor(t + 0.5))) - 1;
            t += stepDelta;
        }
    }

    void WaveForm::generateSawWaveTable() {
        float stepDelta = 1.0 / (AudioSettings::getbufferSize() - 1);
        float t = 0.0;

        for(int i = 0 ; i < AudioSettings::getbufferSize(); i++) {
            sawWaveTable[i] = 2*(t-floor(t + 0.5));
            t += stepDelta;
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
}