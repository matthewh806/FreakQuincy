#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <math.h>
#include "ui/MainWindow.hpp"
#include "engine/Spectrum.hpp"
#include "engine/AudioSettings.hpp"

namespace ui {

    // TODO: Separate class for UI to core engine...!
    // TODO: Button to start / stop audio stream.
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
        setupMainWindow();
    }

    MainWindow::~MainWindow() {
        delete centralWidget;
    }

    void MainWindow::setupMainWindow() {
        centralWidget = new QWidget();
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

        gridLayout = new QGridLayout(this);

        oscillatorWidget = new OscillatorWidget();
        adsrWidget = new ADSRSettingsWidget();
        outputPlotsWidget = new OutputPlotsWidget();
        settingsWidget = new GeneralSettingsWidget();
        masterSettingsWidget = new MasterSettingsWidget();

        gridLayout->addWidget(oscillatorWidget, 0, 0);
        gridLayout->addWidget(adsrWidget, 0, 1);
        gridLayout->addWidget(outputPlotsWidget, 1, 0, 1, 2);
        gridLayout->addWidget(masterSettingsWidget, 2, 0);
        gridLayout->addWidget(settingsWidget, 2, 1);

        gridLayout->setRowMinimumHeight(1, 300);

        centralWidget->setLayout(gridLayout);

        setCentralWidget(centralWidget);
    }

    void MainWindow::plotData(std::vector<double> amplitudes, std::vector<double> frequencies, std::vector<double> powerSpectrum) {
        outputPlotsWidget->plotData(amplitudes, frequencies, powerSpectrum);
    }
}

