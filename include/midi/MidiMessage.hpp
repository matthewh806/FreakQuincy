#ifndef MIDIMESSAGE_HPP
#define MIDIMESSAGE_HPP

#include <iostream>

namespace midi {
    struct MidiMessage {
        uint8_t size = 3;
        uint8_t bytes[3] = {};

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