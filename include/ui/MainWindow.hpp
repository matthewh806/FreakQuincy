#ifndef MAINWINDOW_hpp
#define MAINWINDOW_hpp

#include <QMainWindow>
#include "dep/qcustomplot.h"
#include "ui/OscillatorWidget.hpp"
#include "ui/GeneralSettingsWidget.hpp"
#include "ui/MasterSettingsWidget.hpp"

namespace ui {
    // TODO: This is a bit monolithic right now - split up!
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void plotData(std::vector<double> amplitudes);

        // TODO: Find a way to not have these be public...
        OscillatorWidget *oscillatorWidget;
        MasterSettingsWidget *masterSettingsWidget;
        GeneralSettingsWidget *settingsWidget;

    private:
        QVector<double> x_axis;

        QWidget *centralWidget;
        QGridLayout *gridLayout;
        QCustomPlot *waveformPlot;
        QCustomPlot *spectrumPlot;

        void setupAudioOutput();

        void setupMainWindow();
        void setupPlottingWindow();
    };
}

#endif