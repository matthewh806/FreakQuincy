#ifndef ENGINEUIINTERMEDIARY_HPP
#define ENGINEUIINTERMEDIARY_HPP

#include <QObject>
#include "ui/MainWindow.hpp"
#include "engine/AudioEngine.hpp"
#include "engine/Synth.hpp"

/*
    This class acts as the intermediary between the user event driven UI and 
    the underlying audio and synth engine.

    It is the class which has as members the ui window(s) and the audio engine classes.
 */

namespace ui {
    class EngineUiIntermediary : public QObject {
        Q_OBJECT

        public:
            EngineUiIntermediary();
            ~EngineUiIntermediary();

        public slots:
            void updateUI();

            // Temporary before MIDI implementation - what about with a UI sequencer?
            void noteOn();
            void noteOff();

            void waveformChanged(int);
            void frequencyChanged(double);
            // TODO: Implement this...
            void phaseChanged(double);

        private:
            MainWindow *m_mainWindow = nullptr;
            QTimer *m_timer = nullptr;

            std::shared_ptr<engine::Synth> m_synth;
            std::unique_ptr<engine::AudioEngine> m_engine;
    };
}

#endif