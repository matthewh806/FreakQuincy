#include "midi/MidiInputDevice.hpp"

namespace midi {

    MidiInputDevice::MidiInputDevice() {}
    MidiInputDevice::~MidiInputDevice() {}

    void MidiInputDevice::onMessage(MidiMessage msg) {
        msgQueue.addMessage(msg);
    }
}