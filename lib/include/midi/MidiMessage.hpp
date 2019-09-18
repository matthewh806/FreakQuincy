#ifndef MIDIMESSAGE_HPP
#define MIDIMESSAGE_HPP

#include <iostream>
#include <ostream>
#include <math.h>

namespace midi {

    enum StatusType {
        NOTE_ON = 0x9,
        NOTE_OFF = 0x8,
        UNKNOWN = 0x0 // check if this is sensible...
    };

    // TODO: Store timestamp
    struct MidiMessage {
        uint8_t size = 3;
        uint8_t bytes[3] = {};

        uint8_t getChannel() {
            return bytes[0] & 0x0f;
        }

        void setChannel(uint8_t ch) {
            bytes[0] = (bytes[0] & 0xf0) | (ch & 0x0f);
        }

        uint8_t getStatus() {
            return bytes[0] >> 4;
        }

        void setStatus(uint8_t status) {
            bytes[0] = (bytes[0] & 0xf) | (status << 4);
        }

        StatusType getStatusType() {
            return (StatusType)getStatus();
        }

        uint8_t getNote() {
            return bytes[1];
        }

        void setNote(uint8_t note) {
            bytes[1] = note & 0x7f;
        }

        // e.g. velocity
        uint8_t getValue() {
            return bytes[2];
        }

        void setValue(uint8_t val) {
            bytes[2] = val & 0x7f;
        }

        friend std::ostream& operator<<(std::ostream& out, const MidiMessage& msg)
        {
            for(unsigned int i=0; i<msg.size; i++) {
                out << "Byte " << i << " = " << std::hex << "0x" << (int)msg.bytes[i] << (i==msg.size-1 ? "" : ", ");
            }

            out << std::dec;

            return out;
        }
    };
}

#endif