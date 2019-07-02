#include <QMainWindow>
#include "qcustomplot.h"
#include "WaveFormSignalHandler.hpp"

// TODO: This is a bit monolithic right now - split up!
class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setWaveFormSignalHandler(std::shared_ptr<WaveFormSignalHandler> handler);

    void plotData(std::vector<double> amplitudes);

public slots:
    void sampleRateChanged(int);

private:
    QVector<double> x_axis;

    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *waveformPlot;
    QCustomPlot *spectrumPlot;

    QComboBox *waveformSelector;
    QSpinBox *sampleRateSpinBox;
    QDoubleSpinBox *freqencySpinBox;
    QDoubleSpinBox *phaseSpinBox;

    void setupAudioOutput();

    void setupMainWindow();
    void setupPlottingWindow();

    std::shared_ptr<WaveFormSignalHandler> waveFormSignalHandler;
};