#include <iostream>

#include "ui/EngineUiIntermediary.hpp"
#include "engine/AudioSettings.hpp"
#include "engine/WaveForm.hpp"

namespace ui {
    // TODO: A proper solution for running a process thread - using UI thread for MIDI at the moment is not good...

    EngineUiIntermediary::EngineUiIntermediary() {
        m_synth = std::make_shared<engine::Synth>();
        m_engine = std::unique_ptr<engine::AudioEngine>(new engine::AudioEngine(m_synth));
        m_midiEngine = std::unique_ptr<midi::MidiEngine>(new midi::MidiEngine());

        m_midiEngine->registerMessageCallback(std::bind(&EngineUiIntermediary::midiMessageCallback, this, std::placeholders::_1));

        m_mainWindow = new MainWindow();

        connect(m_mainWindow->oscillatorWidget, SIGNAL(oscTypeChanged(int)), this, SLOT(waveformChanged(int)));
        
        connect(m_mainWindow->adsrWidget, SIGNAL(attackValueChanged(int)), this, SLOT(attackTimeChanged(int)));
        connect(m_mainWindow->adsrWidget, SIGNAL(decayValueChanged(int)), this, SLOT(decayTimeChanged(int)));
        connect(m_mainWindow->adsrWidget, SIGNAL(sustainValueChanged(int)), this, SLOT(sustainLevelChanged(int)));
        connect(m_mainWindow->adsrWidget, SIGNAL(releaseValueChanged(int)), this, SLOT(releaseTimeChanged(int)));
        
        connect(m_mainWindow->settingsWidget, SIGNAL(sampleRateChanged(int)), this, SLOT(sampleRateChanged(int)));
        connect(m_mainWindow->settingsWidget, SIGNAL(legatoToggled(bool)), this, SLOT(legatoToggled(bool)));

        connect(m_mainWindow->masterSettingsWidget, SIGNAL(masterVolumeChanged(float)), this, SLOT(masterVolumeChanged(float)));

        m_mainWindow->oscillatorWidget->setOscType(engine::WaveTypes::SINE);

        m_mainWindow->resize(1024, 900);
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

    void EngineUiIntermediary::attackTimeChanged(int value) {
        std::cout << "New attack: " << value << std::endl;
    }

    void EngineUiIntermediary::decayTimeChanged(int value) {
        std::cout << "New decay: " << value << std::endl;
    }

    void EngineUiIntermediary::sustainLevelChanged(int value) {
        std::cout << "New sustain: " << value << std::endl;
    }

    void EngineUiIntermediary::releaseTimeChanged(int value) {
        std::cout << "New release: " << value << std::endl;
    }

    void EngineUiIntermediary::sampleRateChanged(int rate) {
        engine::AudioSettings::setSampleRate(rate);
    }

    void EngineUiIntermediary::legatoToggled(bool state) {
        std::cout << "Legato Toggled: " << state << std::endl;
    }

    void EngineUiIntermediary::masterVolumeChanged(float vol) {
        engine::AudioSettings::setMasterVolume(vol);
    }
}