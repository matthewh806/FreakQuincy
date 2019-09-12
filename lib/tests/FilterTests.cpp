#include <memory>

#include "catch.hpp"
#include "engine/filters/SecondOrderButterworthLowPassFilter.hpp"

TEST_CASE("FILTER PARAMETERS") {
    std::unique_ptr<engine::filters::SecondOrderButterworthLowPassFilter> filter = 
            std::unique_ptr<engine::filters::SecondOrderButterworthLowPassFilter>(
                new engine::filters::SecondOrderButterworthLowPassFilter(220, 0.1)
    );

    REQUIRE(filter->getCutoff() == 220.0);
    REQUIRE(filter->getResonance() == 0.1);
}