#include <iostream>
#include "engine/Synth.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    Synth::Synth() {

        // Modules
        m_VCOs.insert(std::pair<int, std::unique_ptr<VCO>>(1, std::unique_ptr<VCO>(new VCO(WaveTypes::SINE, 220))));
        m_VCOs.insert(std::pair<int, std::unique_ptr<VCO>>(2, std::unique_ptr<VCO>(new VCO(WaveTypes::SQUARE, 440))));
        m_mixer = std::unique_ptr<Mixer>(new Mixer());
        m_VCA = std::unique_ptr<VCA>(new VCA());

        m_mixer->addVCO(m_VCOs[1].get(), 1);
        m_mixer->addVCO(m_VCOs[2].get(), 0.5);

        // Modulators
        m_LFOs.insert(std::pair<int, std::unique_ptr<LFO>>(1, std::unique_ptr<LFO>(new LFO(WaveTypes::SINE, 1.0, 1.0, false))));
        m_VCOs[1]->attachModulator(m_LFOs[1].get());
    }

    Synth::~Synth() {
        // TODO
    }

    bool Synth::legatoPlay() {
        return AudioSettings::isLegatoEnabled();
    }

    void Synth::noteOn(float freq, bool legatoEvent) {
        bool legato = legatoPlay() && legatoEvent;

        for(const auto& kv : m_VCOs) {
            kv.second->notePressed(freq, legato);
        }

        for(const auto& kv : m_LFOs) {
            kv.second->notePressed(freq, legato);
        }
        
        
        m_VCA->notePressed(freq, legato);
    }

    void Synth::noteOff(bool legatoEvent) {
        bool legato = legatoPlay() && legatoEvent;

        for(const auto& kv : m_VCOs) {
            kv.second->noteReleased(legato);
        }

        for(const auto& kv : m_LFOs) {
            kv.second->noteReleased(legato);
        }

        m_VCA->noteReleased(legato);
    }

    void Synth::setOscFrequency(int idx, double freq) {
        if( m_VCOs.find(idx) == m_VCOs.end())
            return;

        m_VCOs[idx]->setFrequency(freq);
    }

    void Synth::setOscType(int idx, WaveTypes type) {
        if( m_VCOs.find(idx) == m_VCOs.end())
            return;

        m_VCOs[idx]->setWaveType(type);
    }

    float Synth::getVCOMixValue(int idx) {
        if( m_VCOs.find(idx) == m_VCOs.end())
            return 0.0;

        return m_mixer->getVCOWeight(m_VCOs[idx].get());
    }

    void Synth::setVCOMixValue(int idx, float value) {
        if( m_VCOs.find(idx) == m_VCOs.end())
            return;
        
        m_mixer->changeVCOWeight(m_VCOs[idx].get(), value);
    }

    float Synth::getAttack() {
        return m_VCA->getEnvelope()->getAttackTime();
    }

    void Synth::setAttack(float t) {
        m_VCA->getEnvelope()->setAttackTime(t);
    }

    float Synth::getDecay() {
        return m_VCA->getEnvelope()->getDecayTime();
    }

    void Synth::setDecay(float t) {
        m_VCA->getEnvelope()->setDecayTime(t);
    }

    float Synth::getSustain() {
        return m_VCA->getEnvelope()->getSustainLevel();
    }

    void Synth::setSustain(float t) {
        m_VCA->getEnvelope()->setSustainLevel(t);
    }

    float Synth::getRelease() {
        return m_VCA->getEnvelope()->getReleaseTime();
    }

    void Synth::setRelease(float t) {
        m_VCA->getEnvelope()->setReleaseTime(t);
    }

    WaveTypes Synth::getLfoOscType(int idx) { 
        if( m_LFOs.find(idx) == m_LFOs.end())
            return WaveTypes::NOT_SET;

        return m_LFOs[idx]->getWaveType(); 
    }

    void Synth::setLfoOscType(int idx, WaveTypes type) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return;

        m_LFOs[idx]->setWaveType(type);
    }

    float Synth::getLfoFrequency(int idx) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return -1.0;

        return m_LFOs[idx]->getFrequency(); 
    };

    void Synth::setLfoFrequency(int idx, double freq) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return;

        m_LFOs[idx]->setFrequency((float)freq);
    }

    float Synth::getLfoDepth(int idx) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return 0.0;

        return m_LFOs[idx]->getModulationDepth();
    }

    void Synth::setLfoDepth(int idx, double depth) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return;

        m_LFOs[idx]->setModulationDepth(depth);
    }

    bool Synth::getLfoBypassState(int idx) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return false;

        return m_LFOs[idx]->bypass();
    }

    void Synth::setLfoBypass(int idx, bool bypass) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return;

        m_LFOs[idx]->setBypass(bypass);
    }

    Destinations Synth::getLfoDestination(int idx) { 
        if( m_LFOs.find(idx) == m_LFOs.end())
            return Destinations::NONE;

        return m_LFOs[idx]->getDestination(); 
    }

    void Synth::setLfoDestination(int idx, Destinations dest) {
        if( m_LFOs.find(idx) == m_LFOs.end())
            return;


        m_LFOs[idx]->setDestination(dest);
    }

    double Synth::tick() {
        // Tick LFOs first so we can use the last value in the modules
        for(const auto& kv : m_LFOs) {
            kv.second->tick();
        }

        // Tick VCOs to pass to the mixer.
        for(const auto& kv : m_VCOs) {
            kv.second->tick();
        }

        // TODO: This indexing will later be removed and handled by a VCO mixer
        return m_mixer->tick() * m_VCA->tick();
    }
}