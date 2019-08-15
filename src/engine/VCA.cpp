#include "engine/VCA.hpp"

namespace engine {
    VCA::VCA() {
        gain = 1.0;
        envelope = std::unique_ptr<ADSR>(new ADSR(1, 0.2, 0.1, 0.2));
    }

    VCA::~VCA() {}

    double VCA::tick() {
        return gain * envelope->tick();
    }
}