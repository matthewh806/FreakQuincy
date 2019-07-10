#ifndef MIDIENGINE_HPP
#define MIDIENGINE_HPP

#include <vector>
#include "dep/RtMidi.h"
#include "midi/MidiMessage.hpp"

namespace midi {
    class MidiEngine {
        public:
            MidiEngine();
            ~MidiEngine();

            void registerMessageCallback(const std::function<void(MidiMessage)> &cb);
            void onMessage(MidiMessage message);

        private:
            RtMidiIn *midiIn = NULL;
            std::function<void(MidiMessage)> messageCallback = NULL;
            std::vector<std::function<void(MidiMessage)>> messageCallbacks;

            void setupMidi();
            static void midiInCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
    };
}

#endif