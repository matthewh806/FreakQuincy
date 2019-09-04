#include "ui/VCOWidget.hpp"

namespace ui {
    VCOWidget::VCOWidget(QWidget *parent) {
        VCOWidget(tr("VCO"), parent);
    }

    VCOWidget::VCOWidget(const QString& title, QWidget *parent) {
        setTitle(title);
        setup();
    }

    VCOWidget::~VCOWidget() {

    }

    void VCOWidget::setOscType(engine::WaveTypes type) {
        waveformSelector->setOscType(type);
    }

    void VCOWidget::setup() {
        waveformSelector = new WaveformSelectorWidget();

        connect(
            waveformSelector, &WaveformSelectorWidget::oscTypeToggled, 
            this, [=](int type) { this->emit oscTypeChanged(type); }
        );

        vBox = new QVBoxLayout;
        vBox->addWidget(waveformSelector);
        this->setLayout(vBox);
    }
}