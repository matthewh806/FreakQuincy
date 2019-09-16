#ifndef MIDIDEVICE_HPP
#define MIDIDEVICE_HPP

#include <queue>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/bundled/ostream.h"

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
            MidiInputDevice() {
                logger = spdlog::get("Midi");
            };

            ~MidiInputDevice() {};

            virtual int getDeviceId() { return -1; };
            virtual std::string getDeviceName() { return ""; };

            InputQueue msgQueue;
        protected:
            void onMessage(MidiMessage msg);
            virtual void setup() = 0;
            
            std::shared_ptr<spdlog::logger> logger;
    };
}

#endif