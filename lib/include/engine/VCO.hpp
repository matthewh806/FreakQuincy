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

            void setMasterPitchOffset(double pitchOffset) { 
                m_masterPitchOffset = pitchOffset; 
                setFrequency(m_waveForm->getFrequency());
            }
            
            void setFineTuneOffset(double pitchOffset) { 
                m_fineTunePitchOffset = pitchOffset; 
                setFrequency(m_waveForm->getFrequency());
            }

            void setFrequency(double freq); 

            double getLastOut() { return m_lastOut; }

            void notePressed(float freq, bool legato) override { 
                setFrequency(freq);
            };
            
            double tick(double input = 0) override;
        
        private:
            double m_masterPitchOffset = 0.0; // measured in semitones
            double m_fineTunePitchOffset = 0.0; // measured in cents (100 cents in 1 semitone.)
            double m_lastOut;
    };
}

#endif