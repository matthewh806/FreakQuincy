#include "WaveFormSignalHandler.hpp"

WaveFormSignalHandler::WaveFormSignalHandler(std::shared_ptr<WaveForm> waveForm) : m_waveForm(waveForm) {
}

WaveFormSignalHandler::~WaveFormSignalHandler() {

}

void WaveFormSignalHandler::frequencyChanged(double freq) {
    m_waveForm->setFrequency(freq);
}

void WaveFormSignalHandler::phaseChanged(double phase) {
}

void WaveFormSignalHandler::waveformChanged(int index) {
    m_waveForm->set_waveType((WaveTypes)index);
}