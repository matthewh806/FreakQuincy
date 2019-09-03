#ifndef ABSTRACTFILTER_HPP
#define ABSTRACTFILTER_HPP

#include <vector>
#include <iostream>

#include "engine/ModuleBase.hpp"
#include "engine/Modulatable.hpp"

namespace engine {
    namespace filters {
        class AbstractFilter : public ModuleBase, public Modulatable {
            public:
                enum FilterType {
                    LOWPASS = 0,
                    HIGHPASS = 1
                };

                AbstractFilter(double cutoff, double resonance, FilterType type, int y_delays, int x_delays) 
                : 
                m_cutoff(cutoff), 
                m_resonance(resonance), 
                m_type(type),
                m_yDelays(y_delays),
                m_xDelays(x_delays),
                m_y(y_delays),
                m_x(x_delays),
                m_a(y_delays),
                m_b(x_delays)
                {
                };
                
                ~AbstractFilter() {};

                double getCutoff() { return m_cutoff; }
                virtual void setCutoff(double cutoff) = 0;

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
                double tick(double input) final {
                    m_x[0] = input;

                    double sum = 0.0;
                    for(int n = 1; n <= m_yDelays; n++)
                        sum -= m_a[n] * m_y[n];

                    for(int m=0; m <= m_xDelays; m++)
                        sum += m_b[m] * m_x[m];

                    for(int n=m_yDelays; n >= 2; n--)
                        m_y[n] = m_y[n-1];
                    if(m_yDelays > 0)
                        m_y[1] = sum;

                    for(int m=m_xDelays; m >= 2; m--)
                        m_x[m] = m_x[m-1];
                    m_x[1] = m_x[0];

                    return sum;
                }

            protected:
                virtual void calculateCoefficients() = 0;

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
}

#endif