#include <iostream>

#include "EngineUiIntermediary.hpp"

EngineUiIntermediary::EngineUiIntermediary() {
    m_waveForm = std::make_shared<WaveForm>();
    m_waveFormSignalHandler = std::make_shared<WaveFormSignalHandler>(m_waveForm);
    m_engine = std::unique_ptr<AudioEngine>(new AudioEngine(m_waveForm));

    m_mainWindow = new MainWindow();
    m_mainWindow->setWaveFormSignalHandler(m_waveFormSignalHandler);
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