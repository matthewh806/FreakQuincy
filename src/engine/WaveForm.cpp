#include "engine/WaveForm.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {

    // TODO: RESIZE ARRAY IF BUFFER SIZE CHANGES!
    WaveForm::WaveForm() : sineWaveTable(AudioSettings::getbufferSize()), sqrWaveTable(AudioSettings::getbufferSize()),
                            triWaveTable(AudioSettings::getbufferSize()), sawWaveTable(AudioSettings::getbufferSize())
    {
        phase = 0.0;

        generateWaveTables();
    }

    WaveForm::~WaveForm() {
    }

    WaveTypes WaveForm::get_wave_type() const {
        return wType;
    }

    void WaveForm::NotePressed(float freq) {
        setFrequency(freq);
    }
    
    void WaveForm::NoteReleased() {
        // TODO: What happens here?    
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
            return 0.0;

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
        auto stepDelta = 1.0 / (AudioSettings::getbufferSize() - 1);
        auto t = 0.0;

        // Assuming period = 1 here
        for(int i = 0; i < AudioSettings::getbufferSize(); i++) {
            triWaveTable[i] = 2*abs(2*(t - floor(t + 1/2))) - 1;
            t += stepDelta;
        }
    }

    void WaveForm::generateSawWaveTable() {
        auto stepDelta = 1.0 / (AudioSettings::getbufferSize() - 1);
        auto t = 0.0;

        for(int i = 0 ; i < AudioSettings::getbufferSize(); i++) {
            sawWaveTable[i] = 2*(t-floor(t + 1/2));
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