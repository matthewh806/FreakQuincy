#ifndef MODULE_HPP
#define MODULE_HPP

#include <vector>

namespace engine {
    
    class Module {

        public:
            virtual void notePressed(float freq, bool legato) {};
            virtual void noteReleased(bool legato) {};
            virtual double tick() = 0;

            void attachModulator(Module *modulator);
            void detachModulator(Module *modulator);


        private:
            std::vector<Module*> modulators;
    };
}

#endif