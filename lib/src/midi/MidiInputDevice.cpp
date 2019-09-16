#include "midi/MidiInputDevice.hpp"

namespace midi {

    void MidiInputDevice::onMessage(MidiMessage msg) {
        logger->debug(msg);

        msgQueue.addMessage(msg);
    }
}