#include "midi/MidiEngine.hpp"
#include "midi/RtMidiInputDevice.hpp"
#include "midi/ComputerKeyboardInputDevice.hpp"

namespace midi {

    MidiEngine::MidiEngine() {
        setupMidi();
    }

    MidiEngine::~MidiEngine() {

    }

    void MidiEngine::process() {
        if(!curInputDevice) return;

        midi::MidiMessage msg;
        while(curInputDevice->msgQueue.getMessage(&msg)) {
            this->onMessage(msg);
        }
    }

    void MidiEngine::computerKeyPressed(QKeyEvent *event) {
        // TODO: Not very nice or object oriented.
        ComputerKeyboardInputDevice* computerInput = dynamic_cast<ComputerKeyboardInputDevice*>(curInputDevice);
        if(!computerInput)
            return;

        computerInput->keyPressed(event->key());
    }

    void MidiEngine::computerKeyReleased(QKeyEvent *event) {
        ComputerKeyboardInputDevice* computerInput = dynamic_cast<ComputerKeyboardInputDevice*>(curInputDevice);
        if(!computerInput)
            return;

        computerInput->keyReleased(event->key());
    }


    void MidiEngine::onMessage(MidiMessage message) {
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

        RtMidiInputDevice* rtMidi = new RtMidiInputDevice();
        ComputerKeyboardInputDevice* computerMidi = new ComputerKeyboardInputDevice();

        inputDevices.push_back(rtMidi);
        inputDevices.push_back(computerMidi);

        this->setMidiInputDevice(inputDevices[1]);
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
}