#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <math.h>
#include <numeric>
#include "ui/MainWindow.hpp"
#include "engine/Spectrum.hpp"
#include "engine/AudioSettings.hpp"
#include "engine/WaveForm.hpp"

namespace ui {

    // TODO: Separate class for UI to core engine...!
    // TODO: Button to start / stop audio stream.
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
        x_axis = QVector<double>(engine::AudioSettings::getbufferSize());
        std::iota(x_axis.begin(), x_axis.end(), 1);

        setupMainWindow();
    }

    MainWindow::~MainWindow() {
        delete waveformPlot;
        delete spectrumPlot;
        delete centralWidget;
    }

    void MainWindow::setupMainWindow() {
        centralWidget = new QWidget();
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

        gridLayout = new QGridLayout(this);

        oscillatorWidget = new OscillatorWidget();
        adsrWidget = new ADSRSettingsWidget();
        settingsWidget = new GeneralSettingsWidget();
        masterSettingsWidget = new MasterSettingsWidget();

        waveformPlot = new QCustomPlot(centralWidget);
        waveformPlot->setObjectName(QStringLiteral("Waveform Plot"));

        spectrumPlot = new QCustomPlot(centralWidget);
        spectrumPlot->setObjectName(QStringLiteral("Spectrum Plot"));

        gridLayout->addWidget(oscillatorWidget, 0, 0);
        gridLayout->addWidget(adsrWidget, 0, 1);
        gridLayout->addWidget(waveformPlot, 1, 0);
        gridLayout->addWidget(spectrumPlot, 1, 1);
        gridLayout->addWidget(masterSettingsWidget, 2, 0);
        gridLayout->addWidget(settingsWidget, 2, 1);

        gridLayout->setRowMinimumHeight(1, 300);

        centralWidget->setLayout(gridLayout);

        setCentralWidget(centralWidget);
        setupPlottingWindow();

        oscillatorWidget->setOscType(engine::WaveTypes::SINE);
    }

    void MainWindow::setupPlottingWindow() {
        waveformPlot->addGraph();
        waveformPlot->xAxis->setLabel("angle");
        waveformPlot->yAxis->setLabel("Amplitude");
        // waveformPlot->yAxis->setRange(-0.1, 0.1);
        
        spectrumPlot->addGraph();
        spectrumPlot->xAxis->setLabel("frequency");
        spectrumPlot->yAxis->setLabel("Amplitude");
    }

    double hammingWindow(int index, size_t length) {
        double alpha = 0.53836;
        return alpha - (1-alpha) * cos(2 * M_PI * index / (length - 1));
    }

    void MainWindow::plotData(std::vector<double> amplitudes) {
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
        waveformPlot->graph(0)->rescaleAxes();
        waveformPlot->replot();

        spectrumPlot->graph(0)->data()->clear();
        spectrumPlot->graph(0)->setData(frequencies, power_spec);
        spectrumPlot->graph(0)->rescaleAxes();
        spectrumPlot->replot();
    }
}

