#include <iostream>
#include "ui/MixerWidget.hpp"

namespace ui {

    MixerWidget::MixerWidget(QWidget *parent) {
        setTitle(tr("Mixer"));
        setup();
    }

    MixerWidget::~MixerWidget() {}

    void MixerWidget::setMixValue(int id, double v) {
        mixDials[id]->dial->setValue(v);
    }

    void MixerWidget::setup() {
        mixDials.insert({1, createMixerDial(1)});
        mixDials.insert({2, createMixerDial(2)});

        QVBoxLayout *vBox = new QVBoxLayout;
        
        for(const auto& kv : mixDials) {
            vBox->addWidget(kv.second);
        }

        this->setLayout(vBox);
    }

    QLabelDoubleDialWrapper* MixerWidget::createMixerDial(int id) {
        QString labelStr = QString::fromStdString("VCO " + std::to_string(id));
        QLabelDoubleDialWrapper *vcoMixDial = new QLabelDoubleDialWrapper(this, labelStr, 1);
        vcoMixDial->dial->setMinimum(0.0);
        vcoMixDial->dial->setMaximum(1.0);
        vcoMixDial->dial->setSingleStep(0.05);

        connect(vcoMixDial->dial, &QDoubleDial::doubleValueChanged, this, 
            [=](double val) { this->emit mixValChanged(id, val); }
        );

        return vcoMixDial;
    }
}