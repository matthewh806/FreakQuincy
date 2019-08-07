#include <numeric>

#include "ui/OutputPlotsWidget.hpp"
#include "engine/AudioSettings.hpp"

namespace ui {
    OutputPlotsWidget::OutputPlotsWidget(QWidget *parent) {
        setTitle("Output Plots");

        x_axis = QVector<double>(engine::AudioSettings::getbufferSize());
        std::iota(x_axis.begin(), x_axis.end(), 1);

        setup();
    }

    OutputPlotsWidget::~OutputPlotsWidget() {
        delete waveformPlot;
        delete spectrumPlot;
    }

    void OutputPlotsWidget::setup() {
        waveformPlot = new QCustomPlot(this);
        waveformPlot->setObjectName(QStringLiteral("Waveform Plot"));

        spectrumPlot = new QCustomPlot(this);
        spectrumPlot->setObjectName(QStringLiteral("Spectrum Plot"));


        waveformPlot->addGraph();
        waveformPlot->xAxis->setLabel("angle");
        waveformPlot->yAxis->setLabel("Amplitude");
        waveformPlot->yAxis->setRange(-1, 1);
        waveformPlot->xAxis->setRange(x_axis.first(), x_axis.last());
        
        spectrumPlot->addGraph();
        spectrumPlot->xAxis->setLabel("frequency");
        spectrumPlot->yAxis->setLabel("Amplitude");

        hBox = new QHBoxLayout();
        hBox->addWidget(waveformPlot);
        hBox->addWidget(spectrumPlot);

        this->setLayout(hBox);
    }

    void OutputPlotsWidget::plotData(std::vector<double> amplitudes, std::vector<double> frequencies, std::vector<double> powerSpectrum) {
        if(amplitudes.size() != x_axis.size()) {
            x_axis.resize(amplitudes.size());
            std::iota(x_axis.begin(), x_axis.end(), 1);
        }

         // TODO: This modifies vector - not really desirable
        std::for_each(powerSpectrum.begin(), powerSpectrum.end(), [](double &n) { n = 20 * log10(n);});

        QVector<double> amplitudesQvec = QVector<double>::fromStdVector(amplitudes);
        QVector<double> frequenciesQvec = QVector<double>::fromStdVector(frequencies);
        QVector<double> powerSpecQvec = QVector<double>::fromStdVector(powerSpectrum);

        waveformPlot->graph(0)->data()->clear();
        waveformPlot->graph(0)->setData(x_axis, amplitudesQvec);
        waveformPlot->replot();

        spectrumPlot->graph(0)->data()->clear();
        spectrumPlot->graph(0)->setData(frequenciesQvec, powerSpecQvec);
        spectrumPlot->graph(0)->rescaleAxes();
        spectrumPlot->replot();
    }
}