#ifndef MODULATOR_HPP
#define MODULATOR_HPP

#include "engine/ModuleBase.hpp"

namespace engine {
    enum class Destinations {
        PITCH,
        AMP,
        FILTER,
        RESONANCE,
        NONE
    };

    class Modulator : public ModuleBase {
        public:
            double getModulationDepth() { return m_depth; };
            void setModulationDepth(double depth) {
                if(depth > 1.0) depth = 1.0;
                if(depth < 0.0) depth = 0.0;

                m_depth = depth;
            };

            double getLastOut() { return m_lastOut; }

            Destinations getDestination() { return m_destination; }
            void setDestination(Destinations destination) { this->m_destination = destination; }
        
        protected:
            double m_lastOut; // Use this for when tick for current cycle has been performed and we need the val.
            double m_depth = 1.0; // between 0 and 1;
        
        private:
            // TODO: Do these modulators really need to keep track of their destination...?
            Destinations m_destination = Destinations::NONE;
    };
}

#endif