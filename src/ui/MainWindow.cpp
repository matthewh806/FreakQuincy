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
        lfoWidget = new LFOSettingsWidget();
        outputPlotsWidget = new OutputPlotsWidget();
        settingsWidget = new GeneralSettingsWidget();
        masterSettingsWidget = new MasterSettingsWidget();

        gridLayout->addWidget(oscillatorWidget, 0, 0);
        gridLayout->addWidget(adsrWidget, 0, 1);
        gridLayout->addWidget(lfoWidget, 1, 0);
        gridLayout->addWidget(outputPlotsWidget, 2, 0, 1, 2);
        gridLayout->addWidget(masterSettingsWidget, 3, 0);
        gridLayout->addWidget(settingsWidget, 3, 1);

        gridLayout->setRowMinimumHeight(2, 300);

        centralWidget->setLayout(gridLayout);

        setCentralWidget(centralWidget);
    }

    void MainWindow::plotData(std::vector<double> amplitudes, std::vector<double> frequencies, std::vector<double> powerSpectrum) {
        if(!outputPlotsWidget->isVisible())
            return; 
            
        outputPlotsWidget->plotData(amplitudes, frequencies, powerSpectrum);
    }
}

