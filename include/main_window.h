#include <QMainWindow>
#include "qcustomplot.h"
#include "wave_form.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setWave(std::shared_ptr<WaveForm> wave);
    float get_currentFrequency() { return curFreq; };

public slots:
    void sampleRateChanged(int);
    void waveformChanged(int);
    void frequencyChanged(double);
    void phaseChanged(double);

private:
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
    void plotData();

    float curFreq;

    std::shared_ptr<WaveForm> p_wave;
};