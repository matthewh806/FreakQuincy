#ifndef VCO_HPP
#define VCO_HPP

#include "engine/ModuleBase.hpp"
#include "engine/Modulatable.hpp"
#include "engine/Oscillator.hpp"
#include "engine/WaveForm.hpp"

#include "utilities/utilities.hpp"

namespace engine {

    class VCO : public ModuleBase, public Oscillator, public Modulatable {
        public:
            VCO(WaveTypes wType, double freq) : ModuleBase("VCO"), Oscillator(wType, freq) {};
            ~VCO() {};

            double setMasterPitchOffset(double pitchOffset) { m_masterPitchOffset = pitchOffset; }

            double getLastOut() { return m_lastOut; }

            void notePressed(float freq, bool legato) override { 
                float oscFreq = utilities::semitoneShiftToFreq(freq, m_masterPitchOffset);

                logger->debug("id: {}, freq: {}, shiftedFreq: {}", getId(), freq, oscFreq);
                m_waveForm->setFrequency(oscFreq); 
            };
            
            double tick(double input = 0) override;
        
        private:
            double m_masterPitchOffset = 0.0; // measured in semitones
            double m_lastOut;
    };
}

#endif