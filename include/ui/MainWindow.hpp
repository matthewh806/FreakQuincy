#ifndef MAINWINDOW_hpp
#define MAINWINDOW_hpp

#include <QMainWindow>
#include "dep/qcustomplot.h"
#include "ui/OscillatorWidget.hpp"
#include "ui/ADSRSettingsWidget.hpp"
#include "ui/LFOSettingsWidget.hpp"
#include "ui/OutputPlotsWidget.hpp"
#include "ui/GeneralSettingsWidget.hpp"
#include "ui/MasterSettingsWidget.hpp"

namespace ui {
    // TODO: This is a bit monolithic right now - split up!
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void plotData(std::vector<double> amplitudes, std::vector<double> frequencies, std::vector<double> powerSpectrum);

        // TODO: Find a way to not have these be public...
        OscillatorWidget *oscillatorWidget;
        ADSRSettingsWidget *adsrWidget;
        LFOSettingsWidget *lfoWidget;
        OutputPlotsWidget *outputPlotsWidget;
        MasterSettingsWidget *masterSettingsWidget;
        GeneralSettingsWidget *settingsWidget;

    private:
        QWidget *centralWidget;
        QGridLayout *gridLayout;

        void setupAudioOutput();

        void setupMainWindow();
    };
}

#endif