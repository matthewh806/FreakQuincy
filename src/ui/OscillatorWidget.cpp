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
            case engine::WaveTypes::TRIANGLE:
                triButton->toggle();
                break;
            case engine::WaveTypes::SAWTOOTH:
                sawButton->toggle();
                break;
            case engine::WaveTypes::SQUARE:
                squButton->toggle();
                break;
            default:
                break;
        }
    }

    void OscillatorWidget::setup() {
        sinButton = new QRadioButton(tr("Sin"));
        triButton = new QRadioButton(tr("Triangle"));
        sawButton = new QRadioButton(tr("Sawtooth"));
        squButton = new QRadioButton(tr("Square"));

        connect(sinButton, SIGNAL(toggled(bool)), this, SLOT(toggleSin(bool)));
        connect(triButton, SIGNAL(toggled(bool)), this, SLOT(toggleTri(bool)));
        connect(sawButton, SIGNAL(toggled(bool)), this, SLOT(toggleSaw(bool)));
        connect(squButton, SIGNAL(toggled(bool)), this, SLOT(toggleSqu(bool)));

        vBox = new QVBoxLayout;
        vBox->addWidget(sinButton);
        vBox->addWidget(triButton);
        vBox->addWidget(sawButton);
        vBox->addWidget(squButton);
        this->setLayout(vBox);
    }

    void OscillatorWidget::toggleSin(bool checked) {
        if(!checked)
            return;

        emit oscTypeChanged(engine::WaveTypes::SINE);
    }

    void OscillatorWidget::toggleTri(bool checked) {
        if(!checked)
            return;

        emit oscTypeChanged(engine::WaveTypes::TRIANGLE);
    }

    void OscillatorWidget::toggleSaw(bool checked) {
        if(!checked)
            return;

        emit oscTypeChanged(engine::WaveTypes::SAWTOOTH);
    }

    void OscillatorWidget::toggleSqu(bool checked) {
        if(!checked)
            return;

        emit oscTypeChanged(engine::WaveTypes::SQUARE);
    }
}