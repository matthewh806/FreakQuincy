#ifndef FILTERBUILDER_HPP
#define FILTERBUILDER_HPP

#include <memory>

#include "AbstractFilter.hpp"
#include "SecondOrderButterworthLowPassFilter.hpp"

namespace engine {
    namespace filters {
        class FilterBuilder {
            public:
                static std::unique_ptr<AbstractFilter> createButterworthLowPass(double cutoff, double resonance) {
                    return std::unique_ptr<AbstractFilter>(
                        new SecondOrderButterworthLowPassFilter(cutoff, resonance)
                    );
                }
        };
    }
};


#endif