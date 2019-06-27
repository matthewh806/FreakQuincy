#ifndef AudioSettings_hpp
#define AudioSettings_hpp

class AudioSettings {
    public:
        static float getSampleRate() {
            return sampleRate;
        }

        static void setSampleRate(float rate) {
            sampleRate = rate;
        }

        static int getChannels() {
            return channels;
        }

        static void setChannels(int ch) {
            channels = ch;
        }

        static int getbufferSize() {
            return bufferSize;
        }

        static void setBufferSize(int size) {
            bufferSize = size;
        };

    private:
        static float sampleRate;
        static int channels;
        static int bufferSize;
};

#endif