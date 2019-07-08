#ifndef MIDIENGINE_HPP
#define MIDIENGINE_HPP

#include "dep/RtMidi.h"

namespace midi {
    class MidiEngine {
        public:
            MidiEngine();
            ~MidiEngine();

        private:
            RtMidiIn *midiIn = NULL;

            void setupMidi();
            static void midiInCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
    };
}

#endif