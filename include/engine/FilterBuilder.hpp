#ifndef FILTERBUILDER_HPP
#define FILTERBUILDER_HPP

#include <memory>

#include "Filter.hpp"

namespace engine {

    class FilterBuilder {
        public:
         static std::unique_ptr<Filter> createSimplestLowPass(double cutoff, double resonance) {
             return std::unique_ptr<Filter>(
                 new Filter(100, 20, Filter::LOWPASS, {}, {0.5, 0.5})
            );
        }

        static std::unique_ptr<Filter> createSimplestHighPass(double cutoff, double resonance) {
             return std::unique_ptr<Filter>(
                 new Filter(100, 20, Filter::HIGHPASS, {}, {0.5, -0.5})
            );
        }
    };
}


#endif