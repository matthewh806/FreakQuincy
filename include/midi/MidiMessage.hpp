#ifndef MIDIMESSAGE_HPP
#define MIDIMESSAGE_HPP

#include <iostream>

namespace midi {

    enum StatusType {
        NOTE_ON = 0x9,
        NOTE_OFF = 0x8,
        UNKNOWN = 0x0 // check if this is sensible...
    };

    struct MidiMessage {
        uint8_t size = 3;
        uint8_t bytes[3] = {};

        uint8_t getChannel() {
            return bytes[0] & 0x0f;
        }

        uint8_t getStatus() {
            return bytes[0] >> 4;
        }

        StatusType getStatusType() {
            return (StatusType)getStatus();
        }

        uint8_t getNote() {
            return bytes[1];
        }

        // e.g. velocity
        uint8_t getValue() {
            return bytes[2];
        }

        void printBinary() {
            for(unsigned int i=0; i<size; i++) {
                std::cout << "Byte " << i << " = " << std::bitset<8>(bytes[i]) << ", ";
            }

            std::cout << std::endl;
        }

        void printHex() {
            for(unsigned int i=0; i<size; i++) {
                std::cout << "Byte " << i << " = " << std::hex << "0x" << (int)bytes[i] << ", ";
            }

            std::cout << std::dec << std::endl;
        }
    };
}

#endif