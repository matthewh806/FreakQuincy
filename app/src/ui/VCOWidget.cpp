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

        QString tuneLabelStr = QString::fromStdString("Fine Tune (ct)");
        fineTuneDial = new QDoubleDial(tuneLabelStr, this, 2);
        fineTuneDial->setMinimum(-150.0);
        fineTuneDial->setMaximum(150.0);
        fineTuneDial->setSingleStep(5.0);
        fineTuneDial->setValue(0.0);

        connect(fineTuneDial, &QDoubleDial::doubleValueChanged, this,
            [=](double val) { this->emit oscFineTuneValChanged(val); }
        );

        vBox = new QVBoxLayout;
        vBox->addWidget(waveformSelector);
        vBox->addWidget(fineTuneDial);
        this->setLayout(vBox);
    }
}