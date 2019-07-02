#include "AudioEngine.hpp"
#include "AudioSettings.hpp"

AudioEngine::AudioEngine(std::shared_ptr<WaveForm> wave) : p_wave(wave) {
    setupAudioOutput();
}

AudioEngine::~AudioEngine() {

}

void AudioEngine::play(double *output, float waveOutput) {
    output[0] = AudioSettings::volume * waveOutput;
    output[1] = output[0];
}

int AudioEngine::routing(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    AudioEngine *engine = (AudioEngine*) userData;
    
    unsigned int i, j;
    engine->buffer = (double *)outputBuffer;
    std::vector<double> lastValues(AudioSettings::getChannels(), 0);

    if(nBufferFrames != engine->_printBuffer.size()) {
        std::cout << "buffer size changed" << std::endl;
        engine->_printBuffer.resize(nBufferFrames);
    }

    if(status)
        std::cout << "Stream underflow detected!" << std::endl;

    for(i = 0; i < nBufferFrames; i++) {
        play(&lastValues[0], engine->p_wave->get_waveOutput());
        engine->_printBuffer[i] = lastValues[0]; // just one channel to display for now
        for(j = 0; j < 2; j++) {
            *(engine->buffer++) = lastValues[j];
        }
    }

    return 0;
}

void AudioEngine::setupAudioOutput() {
    dac = new RtAudio(RtAudio::MACOSX_CORE);

    if(dac->getDeviceCount() < 1) {
        std::cout << "No audio devices found!" << std::endl;
        return;
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac->getDefaultOutputDevice();
    parameters.nChannels = AudioSettings::getChannels();
    parameters.firstChannel = 0;

    unsigned int bufferFrames = AudioSettings::getbufferSize();
    unsigned int sampleRate = AudioSettings::getSampleRate();

    _printBuffer = std::vector<double>(bufferFrames, 0);

    std::cout << dac->getDeviceInfo(parameters.deviceId).name << std::endl;
    std::cout << dac->getDeviceInfo(parameters.deviceId).preferredSampleRate << std::endl;

    try {
        dac->openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                       48000, &bufferFrames, &routing, this);
        dac->startStream();
    } catch(RtAudioError& e) {
        std::cout << e.getMessage() << std::endl;
        return;
    }
}