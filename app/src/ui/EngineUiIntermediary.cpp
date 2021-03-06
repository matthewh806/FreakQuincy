#include <iostream>

#include "ui/EngineUiIntermediary.hpp"
#include "engine/AudioSettings.hpp"
#include "engine/WaveForm.hpp"
#include "engine/LFO.hpp"

namespace ui {
    // TODO: A proper solution for running a process thread - using UI thread for MIDI at the moment is not good...

    EngineUiIntermediary::EngineUiIntermediary() {
        m_synth = std::make_shared<engine::Synth>();
        m_engine = std::unique_ptr<engine::AudioEngine>(new engine::AudioEngine(m_synth));
        m_midiEngine = std::unique_ptr<midi::MidiEngine>(new midi::MidiEngine());

        m_midiEngine->registerMessageCallback(std::bind(&EngineUiIntermediary::midiMessageCallback, this, std::placeholders::_1));

        m_mainWindow = new MainWindow();

        connect(m_mainWindow->oscillatorWidget->vco1, &VCOWidget::oscTypeChanged, this, 
            [=](int val) {
                m_synth->setOscType(1, (engine::WaveTypes)val);
        });

        connect(m_mainWindow->oscillatorWidget->vco2, &VCOWidget::oscTypeChanged, this, 
            [=](int val) {
                m_synth->setOscType(2, (engine::WaveTypes)val);
        });

        connect(m_mainWindow->oscillatorWidget->vco1, &VCOWidget::oscFineTuneValChanged, this,
            [=](double val) {
                m_synth->setOscFineTune(1, val);
            }
        );

        connect(m_mainWindow->oscillatorWidget->vco2, &VCOWidget::oscFineTuneValChanged, this,
            [=](double val) {
                m_synth->setOscFineTune(2, val);
            }
        );

        connect(m_mainWindow->oscillatorWidget->mixerWidget, &MixerWidget::mixValChanged, this,
            [=](int id, double val) {
                m_synth->setVCOMixValue(id, val);
        });

        connect(m_mainWindow->oscillatorWidget->mixerWidget, &MixerWidget::globalTuneValChanged, this,
            [=](double val) {
                m_synth->setMasterTuneOffset(val);
        });
        
        connect(m_mainWindow->vcaWidget, SIGNAL(ampAttackValChanged(int)), this, SLOT(attackTimeChanged(int)));
        connect(m_mainWindow->vcaWidget, SIGNAL(ampDecayValChanged(int)), this, SLOT(decayTimeChanged(int)));
        connect(m_mainWindow->vcaWidget, SIGNAL(ampSustainValChanged(int)), this, SLOT(sustainLevelChanged(int)));
        connect(m_mainWindow->vcaWidget, SIGNAL(ampReleaseValChanged(int)), this, SLOT(releaseTimeChanged(int)));
        
        connect(m_mainWindow->filterWidget, &FilterWidget::cutoffChanged, this,
            [=](double val) { m_synth->setFilterCutoff(val); }
        );
        connect(m_mainWindow->filterWidget, &FilterWidget::resonanceChanged, this,
            [=](double val) { m_synth->setFilterResonance(val); }
        );

        connect(m_mainWindow->lfoWidget, SIGNAL(oscTypeChanged(int)), this, SLOT(lfoOscTypeChanged(int)));
        connect(m_mainWindow->lfoWidget, SIGNAL(frequencyChanged(double)), this, SLOT(lfoFreqChanged(double)));
        connect(m_mainWindow->lfoWidget, SIGNAL(destinationChanged(int)), this, SLOT(lfoDestinationChanged(int)));
        connect(m_mainWindow->lfoWidget, &LFOSettingsWidget::bypassToggled, this, 
            [=](bool bypass) { 
                m_synth->setLfoBypass(1, bypass);
        });

        connect(m_mainWindow->lfoWidget, &LFOSettingsWidget::depthSliderValueChanged, this,
            [=](double val) {
                m_synth->setLfoDepth(1, val);
        });

        connect(m_mainWindow->settingsWidget, SIGNAL(sampleRateChanged(int)), this, SLOT(sampleRateChanged(int)));
        connect(m_mainWindow->settingsWidget, SIGNAL(legatoToggled(bool)), this, SLOT(legatoToggled(bool)));

        connect(m_mainWindow->masterSettingsWidget, &MasterSettingsWidget::masterVolumeChanged, this,
            [=](float val) { engine::AudioSettings::setMasterVolume(val); }
        );

        m_mainWindow->oscillatorWidget->vco1->setOscType(engine::WaveTypes::SINE);
        m_mainWindow->oscillatorWidget->vco2->setOscType(engine::WaveTypes::SQUARE);

        m_mainWindow->oscillatorWidget->mixerWidget->setMixValue(1, (m_synth->getVCOMixValue(1)));
        m_mainWindow->oscillatorWidget->mixerWidget->setMixValue(2, (m_synth->getVCOMixValue(2)));

        m_mainWindow->vcaWidget->initialize(m_synth->getAttack() * 1000, m_synth->getDecay() * 1000, m_synth->getSustain() * 100, m_synth->getRelease() * 1000);
        
        m_mainWindow->filterWidget->setCutoff(m_synth->getFilterCutoff());
        m_mainWindow->filterWidget->setResonance(m_synth->getFilterResonance());

        m_mainWindow->lfoWidget->setOscType(m_synth->getLfoOscType(1));
        m_mainWindow->lfoWidget->setFrequency(m_synth->getLfoFrequency(1));
        m_mainWindow->lfoWidget->setDestination(m_synth->getLfoDestination(1));
        m_mainWindow->lfoWidget->setBypassState(m_synth->getLfoBypassState(1));

        m_mainWindow->lfoWidget->setModDepth(m_synth->getLfoDepth(1) * 100);

        m_mainWindow->settingsWidget->initializeMidiInOptions(m_midiEngine->getMidiInputDevices());
        m_mainWindow->settingsWidget->initializeAudioOutputOptions(m_engine->getAudioOutputDevices());

        m_mainWindow->resize(1024, 900);
        m_mainWindow->setWindowTitle("FreakQuency");
        m_mainWindow->show(); 

        m_UiTimer = new QTimer(this);
        connect(m_UiTimer, SIGNAL(timeout()), this, SLOT(updateUI()));
        m_UiTimer->start(100); // 100 ms timer
 
        m_midiTimer = new QTimer(this);
        connect(m_midiTimer, &QTimer::timeout, this, [=]() { this->m_midiEngine->process();});
        m_midiTimer->start(1); 

        connect(m_mainWindow, &MainWindow::keyPressedEvent, this, [=](QKeyEvent *event) {
            io::KeyboardEvent* e = new io::KeyboardEvent;
            e->type = io::KEY_PRESS;
            e->key = (io::Key)event->key();

            this->m_midiEngine->computerKeyPressed(e);
        });

        connect(m_mainWindow, &MainWindow::keyReleasedEvent, this, [=](QKeyEvent *event) {
            io::KeyboardEvent* e = new io::KeyboardEvent;
            e->type = io::KEY_RELEASE;
            e->key = (io::Key)event->key();

            this->m_midiEngine->computerKeyReleased(e);
        });

        connect(m_mainWindow->settingsWidget, &GeneralSettingsWidget::midiInputChanged, 
            this, [=](int idx) { this->m_midiEngine->setMidiInputDevice(idx); }
        );

        connect(m_mainWindow->settingsWidget, &GeneralSettingsWidget::audioOutputChanged,
            this, [=](int idx) { this->m_engine->setAudioOutputDevice(idx); }
        );
    }

    EngineUiIntermediary::~EngineUiIntermediary() {
        std::cout << "Kill EngineUiIntermediary" << std::endl;
    }

    void EngineUiIntermediary::updateUI() {
        m_mainWindow->plotData(m_engine->getAudioBuffer(), m_engine->getFrequencies(), m_engine->getPowerSpectrum());
    }

    void EngineUiIntermediary::midiMessageCallback(midi::MidiMessage msg) {        
        switch(msg.getStatusType()) {
            case(midi::StatusType::NOTE_ON): noteOn(); break;
            case(midi::StatusType::NOTE_OFF): noteOff(); break;
            default: std::cout << "UnrecognisedType: " << msg.getStatusType() << std::endl; break; // TODO: Print warning?
        }
    }

    void EngineUiIntermediary::noteOn() {
        m_synth->noteOn(m_midiEngine->getLastNote(), m_midiEngine->notesHeldCount() > 1);
    }

    void EngineUiIntermediary::noteOff() {
        m_synth->noteOff(m_midiEngine->noteHeld());

        // For now just treat it as another noteOn event.
        if(m_midiEngine->noteHeld()) {
            m_synth->noteOn(m_midiEngine->getLastNote(), m_midiEngine->notesHeldCount() >= 1);
        }
    }

    void EngineUiIntermediary::frequencyChanged(double freq) {
        m_synth->setOscFrequency(1, freq);
    }

    void EngineUiIntermediary::phaseChanged(double phase) {
    }

    void EngineUiIntermediary::waveformChanged(int index) {
        m_synth->setOscType(1, (engine::WaveTypes)index);
    }

    void EngineUiIntermediary::attackTimeChanged(int value) {
        m_synth->setAttack(value / 1000.0);
    }

    void EngineUiIntermediary::decayTimeChanged(int value) {
        m_synth->setDecay(value / 1000.0);
    }

    void EngineUiIntermediary::sustainLevelChanged(int value) {
        m_synth->setSustain(value / 100.0);
    }

    void EngineUiIntermediary::releaseTimeChanged(int value) {
        m_synth->setRelease(value / 1000.0);
    }

    void EngineUiIntermediary::lfoOscTypeChanged(int index) {
        m_synth->setLfoOscType(1, (engine::WaveTypes)index);
    }

    void EngineUiIntermediary::lfoFreqChanged(double freq) {
        m_synth->setLfoFrequency(1, freq);
    }

    void EngineUiIntermediary::lfoDestinationChanged(int index) {
        m_synth->setLfoDestination(1, (engine::Destinations)index);
    }

    void EngineUiIntermediary::sampleRateChanged(int rate) {
        engine::AudioSettings::setSampleRate(rate);
    }

    void EngineUiIntermediary::legatoToggled(bool state) {
        engine::AudioSettings::setLegato(state);
    }
}