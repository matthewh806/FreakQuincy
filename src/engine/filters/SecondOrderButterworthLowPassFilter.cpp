#include <math.h>

#include "spdlog/sinks/stdout_color_sinks.h"

#include "engine/filters/SecondOrderButterworthLowPassFilter.hpp"
#include "engine/AudioSettings.hpp"

void engine::filters::SecondOrderButterworthLowPassFilter::setCutoff(double cutoff) {
    m_cutoff = cutoff;
    calculateCoefficients();
}

void engine::filters::SecondOrderButterworthLowPassFilter::calculateCoefficients() {
    // calculate angular frequency 
    // TODO: do we need to warp it...? Text says no - but I don't trust / understand that.
    double w = 2 * M_PI * m_cutoff;

    // derive constants
    double T = 1 / (double)AudioSettings::getSampleRate();
    double J = 4 * m_resonance + 2 * w * T + w * w * m_resonance * T * T;

    m_b[0] = 1 / J * w * w * m_resonance * T * T;
    m_b[1] = 1 / J * 2 * w * w * m_resonance * T * T;
    m_b[2] = 1 / J * w * w * m_resonance * T * T;

    m_a[0] = 1 / J * (-8 * m_resonance + 2 * w * w * m_resonance * T * T);
    m_a[1] = 1 / J * (4 * m_resonance - 2 * w * T + w * w * m_resonance * T * T);

    auto logger = spdlog::get("engine");
    logger->debug("b0: {}, b1: {}, b2: {}, a1: {}, a2: {}", m_b[0], m_b[1], m_b[2], m_a[0], m_a[1]);
}