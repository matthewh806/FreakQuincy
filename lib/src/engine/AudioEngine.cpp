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

        setupAudioEngine();
        p_spectrum = std::unique_ptr<Spectrum>(new Spectrum());
    }

    AudioEngine::~AudioEngine() {

    }

    std::map<int, std::string> AudioEngine::getAudioOutputDevices() {
        std::map<int, std::string> devices;

        if(!dac) {
            devices.insert(std::pair<int, std::string>(0, "No devices found"));
        } else {
            RtAudio::DeviceInfo info;
            for( unsigned int i=0; i<dac->getDeviceCount(); i++) {
                info = dac->getDeviceInfo(i);

                devices.insert(std::pair<int, std::string>(i, info.name));
            }
        }

        return devices;
    }

    void AudioEngine::setAudioOutputDevice(int deviceId) {
        closeStream();

        currentDeviceId = deviceId;
        openStream();
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

    void AudioEngine::setupAudioEngine() {
        dac = new RtAudio(RtAudio::MACOSX_CORE);
        unsigned int devices = dac->getDeviceCount();

        if(devices < 1) {
            logger->error("No audio devices found!");
            return;
        }

        unsigned int bufferFrames = AudioSettings::getbufferSize();
        _printBuffer = std::vector<double>(bufferFrames, 0);

        RtAudio::DeviceInfo info;
        for( unsigned int i=0; i<devices; i++) {
            info = dac->getDeviceInfo(i);

            if(!info.probed)
                continue;
            
            logger->info("Device: {}, name: {}, max. output channels: {}", i, info.name, info.outputChannels);
        }

        unsigned int defaultId = dac->getDefaultOutputDevice();
        logger->info("Default device: {}:{}", defaultId, dac->getDeviceInfo(defaultId).name);
    }

    void AudioEngine::openStream() {
        if(currentDeviceId < 0) {
            // This is a dummy device so do nothing
            return;
        }

        if(dac->isStreamOpen())
            return;

        RtAudio::StreamParameters parameters;
        parameters.deviceId = currentDeviceId;
        parameters.nChannels = AudioSettings::getChannels();
        parameters.firstChannel = 0;

        unsigned int bufferFrames = AudioSettings::getbufferSize();
        unsigned int sampleRate = AudioSettings::getSampleRate();


        try {
             logger->info(
                 "Opening audio device {}:{}, {} outputs",
                 currentDeviceId,
                 dac->getDeviceInfo(parameters.deviceId).name, 
                 dac->getDeviceInfo(parameters.deviceId).outputChannels
            );

            dac->openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                        48000, &bufferFrames, &routing, this);
        } catch(RtAudioError& e) {
            logger->warn("Failed to open audio stream: {}", e.getMessage());
            return;
        }

        try {
            logger->info("Starting audio stream {}", currentDeviceId);
            dac->startStream();
        } catch(RtAudioError& e) {
            logger->warn("Failed to start audio stream: {}", e.what());
        }
    }

    void AudioEngine::closeStream() {
        if(dac->isStreamRunning()) {
            logger->info("Stopping audio stream {}", currentDeviceId);

            try {
                dac->stopStream();
            } catch (RtAudioError& e) {
                logger->warn("Couldn't stop audio stream {}", e.what());
            }
        }

        if(dac->isStreamOpen()) {
            logger->info("Closing audio stream {}", currentDeviceId);

            try {
                dac->closeStream();
            } catch (RtAudioError& e) {
                logger->warn("Couldn't close audio stream {}", e.what());
            }
        }
    }
}