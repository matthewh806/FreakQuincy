#include "engine/VCO.hpp"

namespace engine {
    VCO::VCO() {}
    VCO::~VCO() {}

    void VCO::NotePressed(float freq, bool legato) {
        setFrequency(freq);
    }
}