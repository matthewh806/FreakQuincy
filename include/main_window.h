#include <QMainWindow>
#include "qcustomplot.h"

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

    void setupPlottingWindow();
};