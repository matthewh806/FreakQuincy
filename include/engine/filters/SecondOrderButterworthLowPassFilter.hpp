#ifndef SECONDORDERBUTTERWORTHLOWPASSFILTER_HPP
#define SECONDORDERBUTTERWORTHLOWPASSFILTER_HPP

#include "AbstractFilter.hpp"

namespace engine {
    namespace filters {
        class SecondOrderButterworthLowPassFilter : public AbstractFilter {
            public: 
                SecondOrderButterworthLowPassFilter(double cutoff, double resonance)
                : AbstractFilter(cutoff, resonance, AbstractFilter::LOWPASS, 2, 3) {
                    this->calculateCoefficients();
                }

                ~SecondOrderButterworthLowPassFilter() {};

                void setCutoff(double cutoff) override;
            
            protected:
                void calculateCoefficients() override;
        };
    }
}

#endif