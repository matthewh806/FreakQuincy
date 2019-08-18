#ifndef MODULEBASE_HPP
#define MODULEBASE_HPP

#include <vector>

namespace engine {
    
    class ModuleBase {

        public:
            virtual void notePressed(float freq, bool legato) {};
            virtual void noteReleased(bool legato) {};
            virtual double tick() = 0;
    };
}

#endif