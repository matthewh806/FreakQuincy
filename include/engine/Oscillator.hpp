#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include "engine/Module.hpp"
#include "engine/WaveForm.hpp"

namespace engine {

    class Oscillator : public Module {
        public:
            Oscillator();
            ~Oscillator();

            virtual void notePressed(float freq, bool legato) override;
            virtual double tick() override;
            
            float getFrequency() { return m_waveForm->getFrequency(); }
            virtual void setFrequency(float freq) { m_waveForm->setFrequency(freq); }
            
            WaveTypes getWaveType() { return m_waveForm->getWaveType(); }
            void setWaveType(WaveTypes type) { m_waveForm->setWaveType(type); }
        
        protected:
            std::unique_ptr<WaveForm> m_waveForm;
            
    };
}

#endif