#include <iostream>
#include "engine/Oscillator.hpp"

int main(int argc, char *argv[]) {
    
    engine::Oscillator* osc = new engine::Oscillator();
    osc->setFrequency(300);

    std::cout << osc->getFrequency() << std::endl;

    return 0;
}