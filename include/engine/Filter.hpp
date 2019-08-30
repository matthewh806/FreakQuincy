#ifndef FILTER_HPP
#define FILTER_HPP

#include <vector>
#include <iostream>

#include "engine/ModuleBase.hpp"
#include "engine/Modulatable.hpp"

namespace engine {
    
    class Filter : public ModuleBase, public Modulatable {
        public:
            enum FilterType {
                LOWPASS = 0,
                HIGHPASS = 1
            };

            Filter(double cutoff, double resonance, FilterType type, std::vector<double> a_coeffs, std::vector<double> b_coeffs) 
            : 
            m_cutoff(cutoff), 
            m_resonance(resonance), 
            m_type(type),
            m_yDelays(a_coeffs.size()),
            m_xDelays(b_coeffs.size()),
            m_y(a_coeffs.size()),
            m_x(b_coeffs.size()),
            m_a(a_coeffs),
            m_b(b_coeffs)
            {
            };
            
            ~Filter() {};

            double getCutoff() { return m_cutoff; }
            void setCutoff(double cutoff) { m_cutoff = cutoff;}

            double getResonance() { return m_resonance; }
            void setResonance(double resonance) { m_resonance = resonance; }

            FilterType getType() { return m_type; }
            void setType(FilterType type) { m_type = type; }

            /*
                Performs the calculation
                    y[n] = sum_i=0 to M (b_i . x[n-i]) - sum_j=1 to N (a_j . y[n-j])

                    NOTE: the variables a & b are defined the opposite way around to 
                    in the computer music tutorial book!
            */
            double tick(double input) override;

        private:
            double m_cutoff;
            double m_resonance;
            FilterType m_type;

            int m_yDelays; // N
            int m_xDelays; // M

            std::vector<double> m_y; // N output samples
            std::vector<double> m_x;

            std::vector<double> m_a; // modify feedforward path
            std::vector<double> m_b; // modify feedback path
    };
}

#endif