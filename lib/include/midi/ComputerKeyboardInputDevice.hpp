#ifndef COMPUTERKEYBOARDINPUTDEVICE_HPP
#define COMPUTERKEYBOARDINPUTDEVICE_HPP

#include <map>
#include "io/KeyboardEvent.hpp"
#include "midi/MidiInputDevice.hpp"

namespace midi {
    class ComputerKeyboardInputDevice  : public MidiInputDevice {
        
        public:
            ComputerKeyboardInputDevice();
            ~ComputerKeyboardInputDevice();

            void keyPressed(int key);
            void keyReleased(int key);

            std::string getDeviceName() override { return "ComputerKeyboard"; };

        private:
            const std::map<int, int> keyToNoteMap = {
                {io::Key::Q, 60},
                {io::Key::TWO, 61},
                {io::Key::W, 62},
                {io::Key::THREE, 63},
                {io::Key::E, 64},
                {io::Key::R, 65},
                {io::Key::FIVE, 66},
                {io::Key::T, 67},
                {io::Key::SIX, 68},
                {io::Key::Y, 69},
                {io::Key::SEVEN, 70},
                {io::Key::U, 71},
                {io::Key::U, 72}
            };

            void setup() override;
            void sendMidiEvent(uint8_t note, StatusType type);
    };
}

#endif