#ifndef MODULATABLE_HPP
#define MODULATABLE_HPP

#include "engine/Modulator.hpp"
#include "engine/ModuleBase.hpp"

namespace engine {
    class Modulatable {
        public:
            void attachModulator(Modulator *modulator);
            void detachModulator(Modulator *modulator);

        protected:
            std::vector<Modulator*> m_modulators;
    };
}

#endif