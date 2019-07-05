#include <iostream>

#include "ui/EngineUiIntermediary.hpp"

namespace ui {
    EngineUiIntermediary::EngineUiIntermediary() {
        m_synth = std::make_shared<engine::Synth>();
        m_engine = std::unique_ptr<engine::AudioEngine>(new engine::AudioEngine(m_synth));

        m_mainWindow = new MainWindow();

        connect(m_mainWindow->noteButton, SIGNAL(pressed()), this, SLOT(noteOn()));
        connect(m_mainWindow->noteButton, SIGNAL(released()), this, SLOT(noteOff())); 
        connect(m_mainWindow->waveformSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(waveformChanged(int)));
        connect(m_mainWindow->frequencySpinBox, SIGNAL(valueChanged(double)), this, SLOT(frequencyChanged(double)));
        connect(m_mainWindow->phaseSpinBox, SIGNAL(valueChanged(double)), this, SLOT(phaseChanged(double)));

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

    void EngineUiIntermediary::noteOn() {
        m_synth->noteOn();
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