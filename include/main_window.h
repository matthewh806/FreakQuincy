#include <QMainWindow>
#include "qcustomplot.h"
#include "wave_form.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void frequencyChanged(double);
    void phaseChanged(double);

private:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *waveformPlot;
    QCustomPlot *spectrumPlot;

    QDoubleSpinBox *freqencySpinBox;
    QDoubleSpinBox *phaseSpinBox;

    void setupMainWindow();
    void setupPlottingWindow();
    void plotData();

    std::unique_ptr<WaveForm> p_wave;
};