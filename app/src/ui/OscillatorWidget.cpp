#include "ui/OscillatorWidget.hpp"

namespace ui {
    OscillatorWidget::OscillatorWidget(QWidget *parent) {
        setTitle(tr("Oscillators"));
        setup();
    }

    OscillatorWidget::~OscillatorWidget() {

    }

    void OscillatorWidget::setup() {
        vco1 = new VCOWidget("vco 1", this);
        vco2 = new VCOWidget("vco 2", this);
        mixerWidget = new MixerWidget();

        QWidget *vcoWidget = new QWidget;
        QHBoxLayout *vcoHBox = new QHBoxLayout;
        vcoHBox->addWidget(vco1);
        vcoHBox->addWidget(vco2);
        vcoWidget->setLayout(vcoHBox);

        QVBoxLayout *vBox = new QVBoxLayout;
        vBox->addWidget(vcoWidget);
        vBox->addWidget(mixerWidget);

        this->contentFrame()->setLayout(vBox);
    }
}