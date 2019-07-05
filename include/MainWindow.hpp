#ifndef MAINWINDOW_hpp
#define MAINWINDOW_hpp

#include <QMainWindow>
#include "dep/qcustomplot.h"

// TODO: This is a bit monolithic right now - split up!
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void plotData(std::vector<double> amplitudes);

    // TODO: Temporary before MIDI implemented: DELETE!
    QPushButton *noteButton;

    // TODO: Find a way to not have these be public...
    QComboBox *waveformSelector;
    QSpinBox *sampleRateSpinBox;
    QDoubleSpinBox *frequencySpinBox;
    QDoubleSpinBox *phaseSpinBox;

public slots:
    void sampleRateChanged(int);

private:
    QVector<double> x_axis;

    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *waveformPlot;
    QCustomPlot *spectrumPlot;

    void setupAudioOutput();

    void setupMainWindow();
    void setupPlottingWindow();
};

#endif