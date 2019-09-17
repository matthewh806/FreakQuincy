#ifndef KEYBOARDEVENT_HPP
#define KEYBOARDEVENT_HPP

namespace io {
    
    enum EventType {
        KEY_PRESS,
        KEY_RELEASE
    };

    /*
        Note these map directly to QT values https://doc.qt.io/qt-5/qt.html#Key-enum
        for historial reasons. 
    */
    enum Key {
        Q = 0x51, // C
        TWO = 0x32, // C#
        W = 0x57, // D
        THREE = 0x33, // D#
        E = 0x45, // E
        R = 0x52, // F
        FIVE = 0x35, // F#
        T = 0x54, // G
        SIX = 0x36, // G#
        Y = 0x59, // A
        SEVEN = 0x37, // A#
        U = 0x55, // B
        I = 0x49,
    };

    struct KeyboardEvent {
        EventType type;
        Key key;
    };
}

#endif