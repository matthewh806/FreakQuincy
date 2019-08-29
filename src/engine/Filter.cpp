#include "engine/Filter.hpp"

namespace engine {

    // A do nothing filter! Let everything through
    // Open borders. No discrimination. All frequencies are born equal. 
    //
    // ... but some frequencies are more equal than others. Oink.
    double Filter::tick(double input) {
        return input;
    }

}