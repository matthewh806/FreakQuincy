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

    void MainWindow::keyPressEvent(QKeyEvent *event) {
        if(event->isAutoRepeat())
            return;
            
        emit keyPressedEvent(event);
    }

    void MainWindow::keyReleaseEvent(QKeyEvent *event) {
        if(event->isAutoRepeat())
            return;

        emit keyReleasedEvent(event);
    }

    void MainWindow::setupMainWindow() {
        centralWidget = new QWidget();
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

        gridLayout = new QGridLayout(this);

        oscillatorWidget = new OscillatorWidget();
        vcaWidget = new VCAWidget();
        filterWidget = new FilterWidget();
        lfoWidget = new LFOSettingsWidget();
        outputPlotsWidget = new OutputPlotsWidget();
        settingsWidget = new GeneralSettingsWidget();
        masterSettingsWidget = new MasterSettingsWidget();

        connect(oscillatorWidget, SIGNAL(widgetFolded(QFoldableWidget *)), this, SLOT(onWidgetFolded(QFoldableWidget *)));
        connect(vcaWidget, SIGNAL(widgetFolded(QFoldableWidget *)), this, SLOT(onWidgetFolded(QFoldableWidget *)));
        connect(filterWidget, SIGNAL(widgetFolded(QFoldableWidget *)), this, SLOT(onWidgetFolded(QFoldableWidget *)));
        connect(lfoWidget, SIGNAL(widgetFolded(QFoldableWidget *)), this, SLOT(onWidgetFolded(QFoldableWidget *)));
        connect(settingsWidget, SIGNAL(widgetFolded(QFoldableWidget *)), this, SLOT(onWidgetFolded(QFoldableWidget *)));
        connect(masterSettingsWidget, SIGNAL(widgetFolded(QFoldableWidget *)), this, SLOT(onWidgetFolded(QFoldableWidget *)));

        gridLayout->addWidget(oscillatorWidget, 0, 0);
        gridLayout->addWidget(vcaWidget, 0, 1);
        gridLayout->addWidget(filterWidget, 1, 0);
        gridLayout->addWidget(lfoWidget, 1, 1);
        gridLayout->addWidget(masterSettingsWidget, 2, 0);
        gridLayout->addWidget(settingsWidget, 2, 1);
        gridLayout->addWidget(outputPlotsWidget, 3, 0, 1, 2);

        gridLayout->setRowStretch(0, 0);
        gridLayout->setRowStretch(1, 0);
        gridLayout->setRowStretch(2, 0);
        gridLayout->setRowStretch(3, 1);
        
        gridLayout->setRowMinimumHeight(3, 300);

        centralWidget->setLayout(gridLayout);
        setCentralWidget(centralWidget);
    }

    void MainWindow::plotData(std::vector<double> amplitudes, std::vector<double> frequencies, std::vector<double> powerSpectrum) {
        if(!outputPlotsWidget->isVisible())
            return; 

        outputPlotsWidget->plotData(amplitudes, frequencies, powerSpectrum);
    }

    void MainWindow::onWidgetFolded(QFoldableWidget *widget) {
        // TODO: Check status of neighbours to determine if whole row should collapse.
        // int idx = gridLayout->indexOf(widget);

        // if(idx == -1)
        //     return;

        // int row, column, rowSpan, columnSpan;        
        // gridLayout->getItemPosition(idx, &row, &column, &rowSpan, &columnSpan);
        // gridLayout->setRowMinimumHeight(row, widget->minimumSizeHint().height());
        // std::cout << "row: " << row << ", minHeight: " << gridLayout->rowMinimumHeight(row) << std::endl;

        // centralWidget->QWidget::updateGeometry();
        // centralWidget->adjustSize();
    }
}

