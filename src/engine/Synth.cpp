#include <iostream>
#include "engine/Synth.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    Synth::Synth() {

        // Modules

        m_VCOs.insert(std::pair<int, std::unique_ptr<VCO>>(1, std::unique_ptr<VCO>(new VCO())));
        m_VCA = std::unique_ptr<VCA>(new VCA());

        // Modulators
        m_LFOs.insert(std::pair<int, std::unique_ptr<LFO>>(1, std::unique_ptr<LFO>(new LFO())));
        m_LFOs[1]->setDestination(Destinations::AMP);
        m_LFOs[1]->setFrequency(20);
        m_LFOs[1]->setWaveType(WaveTypes::SINE);
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
        // TODO: This indexing will later be removed and handled by a VCO mixer
        return m_VCOs[1]->tick() * m_VCA->tick();
    }
}