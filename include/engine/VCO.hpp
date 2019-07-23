#ifndef VCO_HPP
#define VCO_HPP

#include "engine/WaveForm.hpp"

namespace engine {

    class VCO : public WaveForm {
        public:
            VCO();
            ~VCO();

            void NotePressed(float freq, bool legato) override;
    };
}

#endif