#ifndef EngineUiIntermediary_HPP
#define EngineUiIntermediary_HPP

#include <QObject>
#include <main_window.h>
#include "AudioEngine.hpp"
#include "wave_form.h"
#include "Synth.hpp"

/*
    This class acts as the intermediary between the user event driven UI and 
    the underlying audio and synth engine.

    It is the class which has as members the ui window(s) and the audio engine classes.
 */

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

        std::shared_ptr<Synth> m_synth;
        std::unique_ptr<AudioEngine> m_engine;
};

#endif