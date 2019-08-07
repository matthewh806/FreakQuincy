#ifndef COMPUTERKEYBOARDINPUTDEVICE_HPP
#define COMPUTERKEYBOARDINPUTDEVICE_HPP

#include <map>
#include <Qt>
#include "midi/MidiInputDevice.hpp"

namespace midi {

    class ComputerKeyboardInputDevice  : public MidiInputDevice {
        public:
            ComputerKeyboardInputDevice();
            ~ComputerKeyboardInputDevice();

            void keyPressed(int key);
            void keyReleased(int key);

        private:
            const std::map<int, int> keyToNoteMap = {
                {Qt::Key_Q, 60},
                {Qt::Key_W, 62},
                {Qt::Key_E, 64},
                {Qt::Key_R, 65},
                {Qt::Key_T, 67},
                {Qt::Key_Y, 69},
                {Qt::Key_U, 71},
            };

            void setup() override;
    };
}

#endif