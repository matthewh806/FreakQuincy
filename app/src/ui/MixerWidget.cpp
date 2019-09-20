#include <iostream>
#include "ui/MixerWidget.hpp"

namespace ui {

    MixerWidget::MixerWidget(QWidget *parent) {
        setTitle(tr("Mixer"));
        setup();
    }

    MixerWidget::~MixerWidget() {}

    void MixerWidget::setMixValue(int id, double v) {
        mixDials[id]->setValue(v);
    }

    void MixerWidget::setup() {
        mixDials.insert({1, createMixerDial(1)});
        mixDials.insert({2, createMixerDial(2)});

        QHBoxLayout *hBox = new QHBoxLayout;
        
        for(const auto& kv : mixDials) {
            hBox->addWidget(kv.second, 0, Qt::AlignHCenter);
        }

        QString tuneLabelStr = QString::fromStdString("Global Tune (st)");
        globalTuneDial = new QDoubleDial(tuneLabelStr, this, 0);
        globalTuneDial->setMinimum(-24.0);
        globalTuneDial->setMaximum(24.0);
        globalTuneDial->setSingleStep(1.0);
        globalTuneDial->setValue(0.0); 

        connect(globalTuneDial, &QDoubleDial::doubleValueChanged, this,
            [=](double val) { this->emit globalTuneValChanged(val); }
        );

        hBox->addWidget(globalTuneDial, 0, Qt::AlignHCenter);
        this->setLayout(hBox);
    }

    QDoubleDial* MixerWidget::createMixerDial(int id) {
        QString labelStr = QString::fromStdString("VCO " + std::to_string(id));
        QDoubleDial *vcoMixDial = new QDoubleDial(labelStr, this, 1);
        vcoMixDial->setMinimum(0.0);
        vcoMixDial->setMaximum(1.0);
        vcoMixDial->setSingleStep(0.05);

        connect(vcoMixDial, &QDoubleDial::doubleValueChanged, this, 
            [=](double val) { this->emit mixValChanged(id, val); }
        );

        return vcoMixDial;
    }
}