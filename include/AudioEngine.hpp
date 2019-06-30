#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "RtAudio.h"
#include "wave_form.h"

class AudioEngine {
    public:
        AudioEngine(std::shared_ptr<WaveForm> wave);
        ~AudioEngine();

    private:
        RtAudio *dac = NULL;
        std::shared_ptr<WaveForm> p_wave;

        static void play(double *output, float waveOutput);
        static int routing(void *outputBuffer, void *intputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

        void setupAudioOutput();
};

#endif