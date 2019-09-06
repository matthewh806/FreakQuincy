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

        QVBoxLayout *vBox = new QVBoxLayout;
        
        for(const auto& kv : mixDials) {
            vBox->addWidget(kv.second, 0, Qt::AlignHCenter);
        }

        this->setLayout(vBox);
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