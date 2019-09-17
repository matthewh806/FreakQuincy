#include <iostream>
#include "midi/ComputerKeyboardInputDevice.hpp"

namespace midi {
    ComputerKeyboardInputDevice::ComputerKeyboardInputDevice() {
        setup();
    }

    ComputerKeyboardInputDevice::~ComputerKeyboardInputDevice() {

    }

    void ComputerKeyboardInputDevice::setup() {
    }

    void ComputerKeyboardInputDevice::keyPressed(int key) {
        auto it = keyToNoteMap.find(key);

        if(it == keyToNoteMap.end()) {
            logger->warn("Key {} not found in keyToNoteMap", key);
            return;
        }

        sendMidiEvent(it->second, StatusType::NOTE_ON);
    }
    
    void ComputerKeyboardInputDevice::keyReleased(int key) {
        auto it = keyToNoteMap.find(key);

        if(it == keyToNoteMap.end()) {
            logger->warn("Key {} not found in keyToNoteMap", key);
            return;
        }

        sendMidiEvent(it->second, StatusType::NOTE_OFF);
    }

    void ComputerKeyboardInputDevice::sendMidiEvent(uint8_t note, StatusType type) {
        midi::MidiMessage msg;
        msg.setStatus(type);
        msg.setNote(note);
        msg.setValue(127);
        
        this->onMessage(msg);
    }
}