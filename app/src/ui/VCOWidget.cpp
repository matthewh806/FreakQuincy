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

        QString phaseOffsetStr = QString::fromStdString("Phase Offset");
        phaseOffsetDial = new QDoubleDial(phaseOffsetStr, this, 2);
        phaseOffsetDial->setMinimum(0.0);
        phaseOffsetDial->setMaximum(360.0);
        phaseOffsetDial->setSingleStep(5.0);
        phaseOffsetDial->setValue(0.0);

        connect(phaseOffsetDial, &QDoubleDial::doubleValueChanged, this,
            [=](double val) { this->emit oscPhaseOffsetValChanged(val); }
        );

        QWidget* dialsWidget = new QWidget;
        QHBoxLayout* dialsHBox = new QHBoxLayout;
        dialsHBox->addWidget(fineTuneDial, 0, Qt::AlignHCenter);
        dialsHBox->addWidget(phaseOffsetDial, 0, Qt::AlignHCenter);
        dialsWidget->setLayout(dialsHBox);

        vBox = new QVBoxLayout;
        vBox->addWidget(waveformSelector);
        vBox->addWidget(dialsWidget);
        this->setLayout(vBox);
    }
}