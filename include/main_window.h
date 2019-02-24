#include <QMainWindow>
#include "qcustomplot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *waveformPlot;
    QCustomPlot *spectrumPlot;

    void setupPlottingWindow();
};