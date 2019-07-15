#include "ui/OscillatorWidget.hpp"

namespace ui {
    OscillatorWidget::OscillatorWidget(QWidget *parent) {
        setTitle(tr("Oscillator"));

        setup();
    }

    OscillatorWidget::~OscillatorWidget() {

    }

    void OscillatorWidget::setOscType(engine::WaveTypes type) {
        switch(type) {
            case engine::WaveTypes::SINE:
                sinButton->toggle();
                break;
            case engine::WaveTypes::SQUARE:
                squButton->toggle();
                break;
        }
    }

    void OscillatorWidget::setup() {
        sinButton = new QRadioButton(tr("Sin"));
        squButton = new QRadioButton(tr("Square"));

        connect(sinButton, SIGNAL(toggled(bool)), this, SLOT(toggleSin(bool)));
        connect(squButton, SIGNAL(toggled(bool)), this, SLOT(toggleSqu(bool)));

        vBox = new QVBoxLayout;
        vBox->addWidget(sinButton);
        vBox->addWidget(squButton);
        this->setLayout(vBox);
    }

    void OscillatorWidget::toggleSin(bool checked) {
        if(!checked)
            return;

        emit oscTypeChanged(engine::WaveTypes::SINE);
    }

    void OscillatorWidget::toggleSqu(bool checked) {
        if(!checked)
            return;

        emit oscTypeChanged(engine::WaveTypes::SQUARE);
    }
}