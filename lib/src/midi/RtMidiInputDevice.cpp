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

    int RtMidiInputDevice::getDeviceId() {
        if(midiIn->isPortOpen())
            return 1;

        return -1;
    }

    std::string RtMidiInputDevice::getDeviceName() {
        if(midiIn->isPortOpen())
            return midiIn->getPortName();
            
        return "";
    }

    void RtMidiInputDevice::setup() {
        try {
            midiIn = new RtMidiIn(RtMidi::MACOSX_CORE);
        } catch(RtMidiError &error) {
            error.printMessage();
            return;
        }

        logger->debug("Port Count: {0}", midiIn->getPortCount());

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

        device->onMessage(msg);
    }
}