#include "engine/Module.hpp"

namespace engine {

    void Module::attachModulator(Module *modulator) {
        auto it = std::find(modulators.begin(), modulators.end(), modulator);

        if(it != modulators.end())
            modulators.push_back(modulator);
    }

    void Module::detachModulator(Module *modulator) {
        auto it = std::find(modulators.begin(), modulators.end(), modulator);

        if(it != modulators.end())
            modulators.erase(it);
    }
}