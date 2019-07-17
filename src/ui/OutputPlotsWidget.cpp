#include <numeric>

#include "ui/OutputPlotsWidget.hpp"
#include "engine/Spectrum.hpp"
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

        setLayout(hBox);
    }

    double hammingWindow(int index, size_t length) {
        double alpha = 0.53836;
        return alpha - (1-alpha) * cos(2 * M_PI * index / (length - 1));
    }

    void OutputPlotsWidget::plotData(std::vector<double> amplitudes) {
        if(amplitudes.size() != x_axis.size()) {
            x_axis.resize(amplitudes.size());
            std::iota(x_axis.begin(), x_axis.end(), 1);
        }

        QVector<double> values_vec = QVector<double>::fromStdVector(amplitudes);

        // TODO: Maybe don't calculate this in the graphics thread...?
        engine::Spectrum* s = new engine::Spectrum(amplitudes.data(), hammingWindow);
        s->generatePowerSpectrum();

        std::vector<double> ps = s->get_powerSpectrum();

        // TODO: This modifies vector - not really desirable
        std::for_each(ps.begin(), ps.end(), [](double &n) { n = 20 * log10(n);});

        QVector<double> frequencies = QVector<double>::fromStdVector(s->get_frequencyRange());
        QVector<double> power_spec = QVector<double>::fromStdVector(ps);

        waveformPlot->graph(0)->data()->clear();
        waveformPlot->graph(0)->setData(x_axis, values_vec);
        waveformPlot->replot();

        spectrumPlot->graph(0)->data()->clear();
        spectrumPlot->graph(0)->setData(frequencies, power_spec);
        spectrumPlot->graph(0)->rescaleAxes();
        spectrumPlot->replot();
    }
}