#ifndef RTMIDIDEVICE_HPP
#define RTMIDIDEVICE_HPP

#include "dep/RtMidi.h"
#include "midi/MidiInputDevice.hpp"

namespace midi {
    class RtMidiInputDevice : public MidiInputDevice {
        public:
            RtMidiInputDevice();
            ~RtMidiInputDevice();

        private:
            RtMidiIn *midiIn = NULL;
            void setup() override;

            static void midiInCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
    };
}

#endif