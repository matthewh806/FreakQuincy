#include <math.h>

#include "engine/filters/SecondOrderButterworthLowPassFilter.hpp"
#include "engine/AudioSettings.hpp"

double engine::filters::SecondOrderButterworthLowPassFilter::calculateTransferFunction(double z) {
    double num;
    double denom;

    num += m_b[0];
    for(int i = 1; i <= m_xDelays; i++)
        num += m_b[i] * pow(z, i);

    denom += 1;
    for(int i=1; i<=m_yDelays; i++) 
        denom += m_a[i] * pow(z, i);

    return num / denom;
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

    logger->debug("b0: {}, b1: {}, b2: {}, a1: {}, a2: {}", m_b[0], m_b[1], m_b[2], m_a[0], m_a[1]);
}