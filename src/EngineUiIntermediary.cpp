#include <iostream>

#include "EngineUiIntermediary.hpp"

EngineUiIntermediary::EngineUiIntermediary() {
    m_synth = std::make_shared<Synth>();
    m_engine = std::unique_ptr<AudioEngine>(new AudioEngine(m_synth));

    m_mainWindow = new MainWindow();
    m_mainWindow->setWaveFormSignalHandler(m_synth->getWaveFormSignalHandler());
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