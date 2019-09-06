#ifndef OUTPUTPlOTSWIDGET_hpp
#define OUTPUTPlOTSWIDGET_hpp

#include <QHBoxLayout>
#include <QGroupBox>
#include "dep/qcustomplot.h"

namespace ui {
    // TODO: Make a custom slider to allow for non linear scaling

    class OutputPlotsWidget : public QGroupBox {
        Q_OBJECT

        public: 
            OutputPlotsWidget(QWidget *parent = nullptr);
            ~OutputPlotsWidget();

            void plotData(std::vector<double> amplitudes, std::vector<double> frequencies, std::vector<double> powerSpectrum);

        private:
            void setup();

            QVector<double> x_axis;

            QHBoxLayout *hBox;
            QCustomPlot *waveformPlot;
            QCustomPlot *spectrumPlot;
    };
}

#endif