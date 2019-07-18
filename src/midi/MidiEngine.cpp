#include "midi/MidiEngine.hpp"

namespace midi {

    MidiEngine::MidiEngine() {
        setupMidi();
    }

    MidiEngine::~MidiEngine() {

    }

    void MidiEngine::onMessage(MidiMessage message) {
        // TODO: Introduce a message queue?
        switch(message.getStatusType()) {
            case(StatusType::NOTE_ON): notePressed(message.getNote(), 1); break;
            case(StatusType::NOTE_OFF): noteReleased(message.getNote(), 1); break;
            default: break;
        }

        for(auto cb : messageCallbacks) cb(message);
    }

    int MidiEngine::notesHeldCount() {
        return heldNotes.size();
    }

    bool MidiEngine::noteHeld() {
        return !heldNotes.empty();
    }

    float MidiEngine::getLastNote() {
        if(heldNotes.empty()) {
            // Figure out what to do here properly
            return 0.0;
        }

        return midiNoteToFreq(heldNotes.back());
    }

    void MidiEngine::setupMidi() {
        heldNotes.reserve(128);

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

    void MidiEngine::notePressed(uint8_t note, int channel) {
        auto res = std::find(heldNotes.begin(), heldNotes.end(), note);
        if(res != heldNotes.end()) {
            heldNotes.erase(res);
        }

        heldNotes.push_back(note);
    }

    void MidiEngine::noteReleased(uint8_t note, int channel) {
        auto res = std::find(heldNotes.begin(), heldNotes.end(), note);

        if(res != heldNotes.end()) {
            heldNotes.erase(res);
        }
    }

    void MidiEngine::registerMessageCallback(const std::function<void(MidiMessage)> &cb) {
        messageCallbacks.push_back(cb);

        std::cout << "Vector size: "  << messageCallbacks.size() << std::endl;
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

        engine->onMessage(msg);
    }
}