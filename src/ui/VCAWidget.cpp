#include "ui/VCAWidget.hpp"

namespace ui {
    VCAWidget::VCAWidget(QWidget *parent) {
        setTitle("amplifier");

        setup();
    }

    VCAWidget::~VCAWidget() {}

    void VCAWidget::setup() {
        adsrWidget = new ADSRSettingsWidget();

        connect(
            adsrWidget, &ADSRSettingsWidget::attackValueChanged,
            this, [=](int val) { this->emit ampAttackValChanged(val);}
        );

        connect(
            adsrWidget, &ADSRSettingsWidget::decayValueChanged,
            this, [=](int val) { this->emit ampDecayValChanged(val);}
        );

        connect(
            adsrWidget, &ADSRSettingsWidget::sustainValueChanged,
            this, [=](int val) { this->emit ampSustainValChanged(val);}
        );

        connect(
            adsrWidget, &ADSRSettingsWidget::releaseValueChanged,
            this, [=](int val) { this->emit ampReleaseValChanged(val);}
        );

        vBox = new QVBoxLayout;
        vBox->addWidget(adsrWidget);

        this->contentFrame()->setLayout(vBox);
    }
}