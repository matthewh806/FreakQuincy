#include <iostream>

#include "ui/EngineUiIntermediary.hpp"

namespace ui {
    // TODO: A proper solution for running a process thread - using UI thread for MIDI at the moment is not good...

    EngineUiIntermediary::EngineUiIntermediary() {
        m_synth = std::make_shared<engine::Synth>();
        m_engine = std::unique_ptr<engine::AudioEngine>(new engine::AudioEngine(m_synth));
        m_midiEngine = std::unique_ptr<midi::MidiEngine>(new midi::MidiEngine());

        m_midiEngine->registerMessageCallback(std::bind(&EngineUiIntermediary::midiMessageCallback, this, std::placeholders::_1));

        m_mainWindow = new MainWindow();

        m_mainWindow->resize(600, 420);
        m_mainWindow->setWindowTitle("FreakQuency");
        m_mainWindow->show();

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(updateUI()));
        m_timer->start(100); // 100 ms timer
    }

    EngineUiIntermediary::~EngineUiIntermediary() {
        std::cout << "Kill EngineUiIntermediary" << std::endl;
    }

    void EngineUiIntermediary::updateUI() {
        std::vector<double> amplitudes = m_engine->getBuffer();
        m_mainWindow->plotData(amplitudes);
    }

    void EngineUiIntermediary::midiMessageCallback(midi::MidiMessage msg) {        
        switch(msg.getStatusType()) {
            case(midi::StatusType::NOTE_ON): noteOn(midi::midiNoteToFreq(msg.getNote())); break;
            case(midi::StatusType::NOTE_OFF): noteOff(); break;
            default: std::cout << "UnrecognisedType: " << msg.getStatusType() << std::endl; break; // TODO: Print warning?
        }
    }

    void EngineUiIntermediary::noteOn(float freq) {
        m_synth->noteOn(freq);
    }

    void EngineUiIntermediary::noteOff() {
        m_synth->noteOff();
    }

    void EngineUiIntermediary::frequencyChanged(double freq) {
        m_synth->setOscFrequency(freq);
    }

    void EngineUiIntermediary::phaseChanged(double phase) {
    }

    void EngineUiIntermediary::waveformChanged(int index) {
        m_synth->setOscType((engine::WaveTypes)index);
    }
}