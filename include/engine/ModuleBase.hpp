#ifndef MODULEBASE_HPP
#define MODULEBASE_HPP

#include <vector>

namespace engine {
    
    /*
    * TODO: If I start to use copy constructors, assignment operators etc
    * this handling of IDs can become problematic.
    * 
    * Also if I save state to disk for e.g. to reload a patch.
    * 
    * WATCH OUT BOY!
    */
    class ModuleBase {

        public:
            ModuleBase() {
                m_id=++counter;
            }

            ~ModuleBase() {};

            virtual void notePressed(float freq, bool legato) {};
            virtual void noteReleased(bool legato) {};
            virtual double tick() = 0;

            int getId() const { return m_id; }

        protected:
            int m_id;

        private:
            static int counter;
    };
}

#endif