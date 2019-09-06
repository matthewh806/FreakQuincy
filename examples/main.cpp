#include <iostream>
#include "engine/Oscillator.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Welcome to examples" << std::endl;

    engine::Oscillator* osc = new engine::Oscillator();
    osc->setFrequency(300);

    std::cout << osc->getFrequency() << std::endl;

    return 0;
}