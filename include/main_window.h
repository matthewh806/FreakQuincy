#include <QMainWindow>
#include "qcustomplot.h"

class MainWindow : public QMainWindow {
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QVBoxLayout *verticalLayout;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupPlottingWindow();

private:

};