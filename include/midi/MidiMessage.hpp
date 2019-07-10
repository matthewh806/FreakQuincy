#ifndef MIDIMESSAGE_HPP
#define MIDIMESSAGE_HPP

#include <iostream>
#include <math.h>

namespace midi {

    enum StatusType {
        NOTE_ON = 0x9,
        NOTE_OFF = 0x8,
        UNKNOWN = 0x0 // check if this is sensible...
    };

    static float midiNoteToFreq(uint8_t midiNote) {
        // TODO: Check midi note value is between 0 - 127

        // TODO: Reference frequency? Default is A4 = 440Hz, m_A4 = 69
        return pow(2, (float)(midiNote - 69)/12.0)*440;
    };

    // TODO: Store timestamp
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