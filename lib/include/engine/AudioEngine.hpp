#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "spdlog/sinks/stdout_color_sinks.h"

#include "dep/RtAudio.h"
#include "engine/Synth.hpp"
#include "engine/Spectrum.hpp"

namespace engine {
    class AudioEngine {
        public:
            AudioEngine(std::shared_ptr<Synth> synth);
            ~AudioEngine();

            std::vector<double> getAudioBuffer() {
                return _printBuffer;
            }

            std::vector<double> getPowerSpectrum() {
                return p_spectrum->get_powerSpectrum();
            }

            std::vector<double> getFrequencies() {
                return p_spectrum->get_frequencyRange();
            }

        private:
            std::shared_ptr<spdlog::logger> logger;
            
            RtAudio *dac = NULL;
            double *buffer;
            std::shared_ptr<Synth> p_synth;
            std::unique_ptr<Spectrum> p_spectrum;
            
            // TODO: I'm maintaining this here just because directly
            // converting the *buffer ptr to vector and trying to display it
            // resulted in garbage plots... but its very wasteful to maintain this twice
            // so figure out why...

            // is the engine consuming the buffer data...?
            std::vector<double> _printBuffer;

            static void play(double *output, float waveOutput);
            static int routing(void *outputBuffer, void *intputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

            void setupAudioOutput();
    };
}

#endif