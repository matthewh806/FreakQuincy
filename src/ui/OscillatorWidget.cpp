#include "ui/OscillatorWidget.hpp"

namespace ui {
    OscillatorWidget::OscillatorWidget(QWidget *parent) {
        setTitle(tr("Oscillator"));

        setup();
    }

    OscillatorWidget::~OscillatorWidget() {

    }

    void OscillatorWidget::setOscType(engine::WaveTypes type) {
        waveformSelector->setOscType(type);
    }

    void OscillatorWidget::setup() {
        waveformSelector = new WaveformSelectorWidget();

        connect(
            waveformSelector, &WaveformSelectorWidget::oscTypeToggled, 
            this, [=](int type) { this->emit oscTypeChanged(type); }
        );

        vBox = new QVBoxLayout;
        vBox->addWidget(waveformSelector);
        this->contentFrame()->setLayout(vBox);
    }
}