#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "dep/RtAudio.h"
#include "engine/Synth.hpp"

namespace engine {
    class AudioEngine {
        public:
            AudioEngine(std::shared_ptr<Synth> synth);
            ~AudioEngine();

            std::vector<double> getBuffer() {
                return _printBuffer;
            }

        private:
            RtAudio *dac = NULL;
            double *buffer;
            std::shared_ptr<Synth> p_synth;
            
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