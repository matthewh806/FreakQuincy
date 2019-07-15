#include "ui/OscillatorWidget.hpp"

namespace ui {
    OscillatorWidget::OscillatorWidget(QWidget *parent) {
        setTitle(tr("Oscillator"));

        setup();
    }

    OscillatorWidget::~OscillatorWidget() {

    }

    void OscillatorWidget::setup() {
        sinButton = new QRadioButton(tr("Sin"));
        squButton = new QRadioButton(tr("Square"));

        vBox = new QVBoxLayout;
        vBox->addWidget(sinButton);
        vBox->addWidget(squButton);
        this->setLayout(vBox);
    }
}