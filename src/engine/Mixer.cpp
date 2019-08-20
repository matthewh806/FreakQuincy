#include "engine/Mixer.hpp"

namespace engine {

    /*
    *  Not the responsibility of the mixer to call tick - do assume 
    *  it has already been done by this point.
    * 
    *  m(t) = sum_i (weight_i * f_i) / sum_i (weight_i)
    * 
    *  f(t) gives the output of the vco for the current tick
    */
    double Mixer::tick() {
        double sum_weights = 0.0f;
        double sum_vco_output = 0.0f;

        for(const auto& kv : m_vco_weights) {
            sum_weights += kv.second;
            sum_vco_output += (kv.first->getLastOut() * kv.second);
        }

        if(sum_weights <= 0.0)
            return 0.0;

        return sum_vco_output / sum_weights;
    }
}