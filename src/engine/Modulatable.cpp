#include "engine/Modulatable.hpp"

namespace engine {

    void Modulatable::attachModulator(Modulator *modulator) {
        auto it = std::find(m_modulators.begin(), m_modulators.end(), modulator);

        if(it != m_modulators.end())
            m_modulators.push_back(modulator);
    }

    void Modulatable::detachModulator(Modulator *modulator) {
        auto it = std::find(m_modulators.begin(), m_modulators.end(), modulator);

        if(it != m_modulators.end())
            m_modulators.erase(it);
    }
}