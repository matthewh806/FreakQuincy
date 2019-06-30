#ifndef EngineUiIntermediary_HPP
#define EngineUiIntermediary_HPP

#include <QObject>
#include "AudioEngine.hpp"
#include "wave_form.h"
#include "WaveFormSignalHandler.hpp"
#include <main_window.h>

class EngineUiIntermediary : public QObject {
    Q_OBJECT

    public:
        EngineUiIntermediary();
        ~EngineUiIntermediary();

    public slots:
        void updateUI();

    private:
        MainWindow *m_mainWindow = nullptr;
        QTimer *m_timer = nullptr;

        std::shared_ptr<WaveForm> m_waveForm;
        std::shared_ptr<WaveFormSignalHandler> m_waveFormSignalHandler;
        std::unique_ptr<AudioEngine> m_engine;
};

#endif