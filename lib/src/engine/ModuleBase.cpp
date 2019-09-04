#include "engine/ModuleBase.hpp"

namespace engine {
    int ModuleBase::counter = 0;
    
    bool operator==(const ModuleBase& lhs, const ModuleBase& rhs) { return lhs.getId() == rhs.getId(); }
}