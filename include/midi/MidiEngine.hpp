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

            int notesHeldCount();
            bool noteHeld();
            float getLastNote();

        private:
            RtMidiIn *midiIn = NULL;
            std::function<void(MidiMessage)> messageCallback = NULL;
            std::vector<std::function<void(MidiMessage)>> messageCallbacks;

            std::vector<uint8_t> heldNotes;

            static void midiInCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
            
            void setupMidi();
            void notePressed(uint8_t note, int channel);
            void noteReleased(uint8_t note, int channel);
    };
}

#endif