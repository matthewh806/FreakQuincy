#include "midi/MidiEngine.hpp"
#include "midi/MidiMessage.hpp"

namespace midi {

    MidiEngine::MidiEngine() {
        setupMidi();
    }

    MidiEngine::~MidiEngine() {

    }

    void MidiEngine::setupMidi() {
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

        midiIn->setCallback(&midiInCallback);
        midiIn->ignoreTypes(true, true, true);
    }

    void MidiEngine::midiInCallback(double deltatime, std::vector<unsigned char> *message, void *userData) {

        MidiEngine *engine = (MidiEngine*) userData;

        unsigned int nBytes = message->size();

        if(nBytes > 3) return; // This is a problem...

        MidiMessage msg;
        msg.size = nBytes;

        for(unsigned int i=0; i<nBytes; i++) {
            msg.bytes[i] = message->at(i);
        }

        msg.printBinary();
        msg.printHex();
    }
}