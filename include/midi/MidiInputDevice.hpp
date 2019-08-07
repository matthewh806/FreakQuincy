#ifndef MIDIDEVICE_HPP
#define MIDIDEVICE_HPP

#include <queue>
#include "midi/MidiMessage.hpp"

namespace midi {
    struct InputQueue {
        std::queue<MidiMessage> msgQueue;

        void addMessage(MidiMessage msg) {
            msgQueue.push(msg);
        }

        bool getMessage(MidiMessage* msg) {
            if(msgQueue.empty())
                return false;
            
            *msg = msgQueue.front();
            msgQueue.pop();
            return true;
        }
    };

    class MidiInputDevice {
        public:
            MidiInputDevice();
            ~MidiInputDevice();

            InputQueue msgQueue; 
        protected:
            void onMessage(MidiMessage msg);
            virtual void setup() = 0;
    };
}

#endif