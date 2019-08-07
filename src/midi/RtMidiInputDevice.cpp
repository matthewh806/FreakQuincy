#include "midi/RtMidiInputDevice.hpp"

namespace midi {

    RtMidiInputDevice::RtMidiInputDevice() {
        setup();
    }

    RtMidiInputDevice::~RtMidiInputDevice() {
        if(!midiIn)
            return;
            
        midiIn->closePort();
        delete midiIn;
    }

    void RtMidiInputDevice::setup() {
        try {
            midiIn = new RtMidiIn(RtMidi::MACOSX_CORE);
        } catch(RtMidiError &error) {
            error.printMessage();
            return;
        }

        std::cout << "Port Count: " << midiIn->getPortCount() << std::endl;

        try {
            // TODO: Give option?
            midiIn->openPort(0);
        } catch(RtMidiError &error) {
            error.printMessage();
            return;
        }

        midiIn->setCallback(&midiInCallback, this);
        midiIn->ignoreTypes(true, true, true);
    }

    void RtMidiInputDevice::midiInCallback(double deltatime, std::vector<unsigned char> *message, void *userData) {

        RtMidiInputDevice *device = (RtMidiInputDevice*) userData;

        unsigned int nBytes = message->size();

        if(nBytes > 3) return; // This is a problem...

        MidiMessage msg;
        msg.size = nBytes;

        for(unsigned int i=0; i<nBytes; i++) {
            msg.bytes[i] = message->at(i);
        }

        msg.printBinary();
        msg.printHex();

        device->onMessage(msg);
    }
}