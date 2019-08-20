#include "ui/MixerWidget.hpp"

namespace ui {

    MixerWidget::MixerWidget(QWidget *parent) {
        setTitle(tr("Mixer"));
        setup();
    }

    MixerWidget::~MixerWidget() {}

    void MixerWidget::setMixValue(int id, int v) {
        mixDials[id]->setValue(v);
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

    QDial* MixerWidget::createMixerDial(int id) {
        QDial *vcoMixDial = new QDial();
        vcoMixDial->setMinimum(0);
        vcoMixDial->setMaximum(100);
        vcoMixDial->setSingleStep(5);

        connect(vcoMixDial, &QDial::valueChanged, this, 
            [=](int val) { this->emit mixValChanged(id, val); 
        });

        return vcoMixDial;
    }
}