#ifndef COMPUTERKEYBOARDINPUTDEVICE_HPP
#define COMPUTERKEYBOARDINPUTDEVICE_HPP

#include <map>
#include "midi/MidiInputDevice.hpp"

namespace midi {
    class ComputerKeyboardInputDevice  : public MidiInputDevice {

        enum KEY {
            Key_Q = 0x51,
            Key_W = 0x57  
        };
        
        public:
            ComputerKeyboardInputDevice();
            ~ComputerKeyboardInputDevice();

            void keyPressed(int key);
            void keyReleased(int key);

            std::string getDeviceName() override { return "ComputerKeyboard"; };

        private:
            const std::map<int, int> keyToNoteMap = {
                {KEY::Key_Q, 60},
                {KEY::Key_W, 62}
                // {Qt::Key_E, 64},
                // {Qt::Key_R, 65},
                // {Qt::Key_T, 67},
                // {Qt::Key_Y, 69},
                // {Qt::Key_U, 71},
            };

            void setup() override;
    };
}

#endif