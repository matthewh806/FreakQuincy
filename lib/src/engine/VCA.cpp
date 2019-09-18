#include "engine/VCA.hpp"
#include "engine/ExponentialTimeADSR.hpp"
#include "engine/LinearTimeADSR.hpp"

namespace engine {
    VCA::VCA() : ModuleBase("VCA") {
        gain = 1.0;
        envelope = std::unique_ptr<AbstractEnvelope>(new ExponentialTimeADSR(1, 0.2, 0.1, 0.2, 1.0, false));
    }

    VCA::~VCA() {}

    double VCA::tick(double input) {
        float modVal = 1.0;

        for(const auto& m : m_modulators) {
            if(m->bypass()) continue;
            modVal *= m->getLastOut();

        }

        return gain * envelope->tick() * modVal;
    }
}