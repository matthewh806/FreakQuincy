#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "RtAudio.h"
#include "wave_form.h"

class AudioEngine {
    public:
        AudioEngine(std::shared_ptr<WaveForm> wave);
        ~AudioEngine();

        // TODO: Is this safe? Can it be modified from elsewhere if we're just returning a pointer to the data...? (surely yes)
        // Maybe here I should convert it to a vector already?

        // and what about the size...?

        std::vector<double> getBuffer() {
            return std::vector<double>(buffer, buffer+buffer_size);
        }

    private:
        RtAudio *dac = NULL;
        double *buffer;
        int buffer_size;
        std::shared_ptr<WaveForm> p_wave;

        static void play(double *output, float waveOutput);
        static int routing(void *outputBuffer, void *intputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

        void setupAudioOutput();
};

#endif