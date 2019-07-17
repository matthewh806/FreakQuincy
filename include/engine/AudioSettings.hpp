#ifndef AUDIOSETTINGS_HPP
#define AUDIOSETTINGS_HPP

namespace engine {
    class AudioSettings {
        public:
            static int getSampleRate() {
                return sampleRate;
            }

            static void setSampleRate(int rate) {
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

            static float getMasterVolume() {
                return masterVolume;
            }

            static void setMasterVolume(float v) {
                if(v > 1.0f) 
                    v = 1.0f;
                
                if(v < 0.0f)
                    v = 0.0f;

                masterVolume = v;
            }

        private:
            static float masterVolume;
            static int sampleRate;
            static int channels;
            static int bufferSize;
    };
}

#endif