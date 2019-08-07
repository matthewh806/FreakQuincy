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
                {Qt::Key_Q, 60}
            };

            void setup() override;
    };
}

#endif