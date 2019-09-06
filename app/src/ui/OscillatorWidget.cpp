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
        QVBoxLayout *vcoVBox = new QVBoxLayout;
        vcoVBox->addWidget(vco1);
        vcoVBox->addWidget(vco2);
        vcoWidget->setLayout(vcoVBox);


        QHBoxLayout *hBox = new QHBoxLayout;
        hBox->addWidget(vcoWidget);
        hBox->addWidget(mixerWidget);

        this->contentFrame()->setLayout(hBox);
    }
}