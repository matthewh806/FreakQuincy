#ifndef EngineUiIntermediary_HPP
#define EngineUiIntermediary_HPP

#include <QObject>
#include <main_window.h>
#include "AudioEngine.hpp"
#include "wave_form.h"
#include "WaveFormSignalHandler.hpp"
#include "Synth.hpp"

class EngineUiIntermediary : public QObject {
    Q_OBJECT

    public:
        EngineUiIntermediary();
        ~EngineUiIntermediary();

    public slots:
        void updateUI();
        void noteOn();
        void noteOff();

    private:
        MainWindow *m_mainWindow = nullptr;
        QTimer *m_timer = nullptr;

        std::shared_ptr<Synth> m_synth;
        std::unique_ptr<AudioEngine> m_engine;
};

#endif