#include <QHBoxLayout>
#include "ui/FilterWidget.hpp"

namespace ui {

    FilterWidget::FilterWidget(QWidget *parent) : QFoldableWidget(parent) {
        setTitle("Filter");
        setup();
    }

    FilterWidget::~FilterWidget() {

    }

    void FilterWidget::setup() {
        cutoffDial = new QDoubleDial("Cutoff", this, 1);
        cutoffDial->setMinimum(20);
        cutoffDial->setMaximum(18000);
        cutoffDial->setSingleStep(100);
        connect(cutoffDial, &QDial::valueChanged, this, 
            [=](double val) { this->emit cutoffChanged(val); }
        );

        resonanceDial = new QDoubleDial("Resonance", this, 1);
        resonanceDial->setMinimum(0.1);
        resonanceDial->setMaximum(1.0);
        resonanceDial->setSingleStep(0.1);
        connect(resonanceDial, &QDial::valueChanged, this, 
            [=](double val) { this->emit resonanceChanged(val); }
        );

        QHBoxLayout *hBox = new QHBoxLayout;
        hBox->addWidget(cutoffDial);
        hBox->addWidget(resonanceDial);

        this->contentFrame()->setLayout(hBox);
    }
}