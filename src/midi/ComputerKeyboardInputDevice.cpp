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

        std::cout << "keyPressed" << key << std::endl;

        if(it == keyToNoteMap.end()) {
            return;
        }

        midi::MidiMessage msg;
        msg.setStatus(StatusType::NOTE_ON);
        msg.setNote(it->second);
        msg.setValue(127);
        
        this->onMessage(msg);
    }
    
    void ComputerKeyboardInputDevice::keyReleased(int key) {
        auto it = keyToNoteMap.find(key);

        std::cout << "keyReleased" << key << std::endl;

        if(it == keyToNoteMap.end())
            return;

        midi::MidiMessage msg;
        msg.setStatus(StatusType::NOTE_OFF);
        msg.setNote(it->second);
        msg.setValue(127);
        
        this->onMessage(msg);
    }
}