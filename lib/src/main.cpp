#include <iostream>

#include "engine/Oscillator.hpp"
#include "engine/filters/SecondOrderButterworthLowPassFilter.hpp"

int main(int argc, char *argv[]) {
    engine::Oscillator* osc = new engine::Oscillator();
    osc->setFrequency(300);

    return 0;
}