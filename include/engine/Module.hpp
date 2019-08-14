#ifndef MODULE_HPP
#define MODULE_HPP

namespace engine {
    
    class Module {

        public:
            virtual void notePressed(float freq, bool legato) {};
            virtual void noteReleased(bool legato) {};

            virtual double tick() = 0;
    };
}

#endif