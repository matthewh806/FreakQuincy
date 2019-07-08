#include "midi/MidiEngine.hpp"

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
        unsigned int nBytes = message->size();

        for(unsigned int i=0; i<nBytes; i++) {
            std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
        }

        if(nBytes > 0) {
            std::cout << "stamp = " << deltatime << std::endl;
        }
    }
}