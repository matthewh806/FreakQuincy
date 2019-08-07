#ifndef MIDIENGINE_HPP
#define MIDIENGINE_HPP

#include <vector>
// TODO: Wrap in custom event class to avoid this here
#include <QKeyEvent>
#include "dep/RtMidi.h"
#include "midi/MidiInputDevice.hpp"
#include "midi/MidiMessage.hpp"

namespace midi {
    class MidiEngine {
        public:
            MidiEngine();
            ~MidiEngine();

            void registerMessageCallback(const std::function<void(MidiMessage)> &cb);
            void onMessage(MidiMessage message);

            void process();

            void computerKeyPressed(QKeyEvent *event);
            void computerKeyReleased(QKeyEvent *event);
            
            void setMidiInputDevice(MidiInputDevice* input) { curInputDevice = input; }
            MidiInputDevice* getMidiInputDevice() { return curInputDevice; }

            int notesHeldCount();
            bool noteHeld();
            float getLastNote();

        private:
            std::vector<MidiInputDevice*> inputDevices;
            MidiInputDevice* curInputDevice = NULL;

            std::function<void(MidiMessage)> messageCallback = NULL;
            std::vector<std::function<void(MidiMessage)>> messageCallbacks;

            std::vector<uint8_t> heldNotes;
            
            void setupMidi();
            void notePressed(uint8_t note, int channel);
            void noteReleased(uint8_t note, int channel);
    };
}

#endif