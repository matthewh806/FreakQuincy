#include "catch.hpp"
#include "engine/filters/SecondOrderButterworthLowPassFilter.hpp"

SecondOrderButterworthLowPassFilter filter = new SecondOrderButterworthLowPassFilter(1000, 0.7);

TEST_CASE( "Cutoff Freq is 1000", "[Filter]") {
    REQUIRE( filter->getCutoff() == 1000);
}