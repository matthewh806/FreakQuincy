#ifndef FILTER_HPP
#define FILTER_HPP

#include "engine/ModuleBase.hpp"
#include "engine/Modulatable.hpp"

namespace engine {
    
    class Filter : public ModuleBase, public Modulatable {
        public:
            enum FilterType {
                LOWPASS = 0,
                HIGHPASS = 1
            };

            Filter(double cutoff, double resonance, FilterType type) 
            : m_cutoff(cutoff), 
            m_resonance(resonance), 
            m_type(type) 
            {};
            
            ~Filter() {};

            double getCutoff() { return m_cutoff; }
            void setCutoff(double cutoff) { m_cutoff = cutoff;}

            double getResonance() { return m_resonance; }
            void setResonance(double resonance) { m_resonance = resonance; }

            FilterType getType() { return m_type; }
            void setType(FilterType type) { m_type = type; }

            double tick(double input) override;

        private:
            double m_cutoff;
            double m_resonance;
            FilterType m_type;
    };
}

#endif