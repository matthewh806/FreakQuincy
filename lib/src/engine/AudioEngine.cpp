#include "engine/AudioEngine.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    
    // TODO: Find somewhere more apt. for this
    double hammingWindow(int index, size_t length) {
        double alpha = 0.53836;
        return alpha - (1-alpha) * cos(2 * M_PI * index / (length - 1));
    }
    
    AudioEngine::AudioEngine(std::shared_ptr<Synth> synth) : p_synth(synth) {
        logger = spdlog::stdout_color_mt("AudioEngine");

        setupAudioOutput();
        p_spectrum = std::unique_ptr<Spectrum>(new Spectrum());
    }

    AudioEngine::~AudioEngine() {

    }

    void AudioEngine::play(double *output, float synthOutput) {
        output[0] = AudioSettings::getMasterVolume() * synthOutput;
        output[1] = output[0];
    }

    int AudioEngine::routing(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
        AudioEngine *engine = (AudioEngine*) userData;
        
        unsigned int i, j;
        engine->buffer = (double *)outputBuffer;
        std::vector<double> lastValues(AudioSettings::getChannels(), 0);

        if(nBufferFrames != engine->_printBuffer.size()) {
            engine->logger->info("buffer size changed");
            engine->_printBuffer.resize(nBufferFrames);
        }

        if(status)
            engine->logger->warn("Stream underflow detected!");

        for(i = 0; i < nBufferFrames; i++) {
            play(&lastValues[0], engine->p_synth->tick());
            engine->_printBuffer[i] = lastValues[0]; // just one channel to display for now
            for(j = 0; j < 2; j++) {
                *(engine->buffer++) = lastValues[j];
            }
        }

        engine->p_spectrum->generatePowerSpectrum(engine->getAudioBuffer().data(), hammingWindow);

        return 0;
    }

    void AudioEngine::setupAudioOutput() {
        dac = new RtAudio(RtAudio::MACOSX_CORE);

        if(dac->getDeviceCount() < 1) {
            logger->error("No audio devices found!");
            return;
        }

        RtAudio::StreamParameters parameters;
        parameters.deviceId = dac->getDefaultOutputDevice();
        parameters.nChannels = AudioSettings::getChannels();
        parameters.firstChannel = 0;

        unsigned int bufferFrames = AudioSettings::getbufferSize();
        unsigned int sampleRate = AudioSettings::getSampleRate();

        _printBuffer = std::vector<double>(bufferFrames, 0);

        logger->info(
            "device ID: {}, sample rate {}", 
            dac->getDeviceInfo(parameters.deviceId).name, 
            dac->getDeviceInfo(parameters.deviceId).preferredSampleRate
        );

        try {
            dac->openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                        48000, &bufferFrames, &routing, this);
            dac->startStream();
        } catch(RtAudioError& e) {
            logger->error(e.getMessage());;
            return;
        }
    }
}