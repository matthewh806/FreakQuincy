#include <Qt>
#include "ui/ADSRSettingsWidget.hpp"

namespace ui {
    ADSRSettingsWidget::ADSRSettingsWidget(QWidget *parent) {
        setTitle("ADSR");

        setup();
    }

    ADSRSettingsWidget::~ADSRSettingsWidget() {
    }

    void ADSRSettingsWidget::setup() {
        
        attackSlider = new QSlider(Qt::Vertical);
        attackSlider->setMinimum(100);
        attackSlider->setMaximum(4000);
        attackSlider->setSingleStep(100);
        attackSlider->setTickPosition(QSlider::TicksLeft);
        connect(attackSlider, SIGNAL(valueChanged(int)), this, SLOT(attackSliderValueChanged(int)));

        decaySlider = new QSlider(Qt::Vertical);
        decaySlider->setMinimum(100);
        decaySlider->setMaximum(4000);
        decaySlider->setSingleStep(100);
        decaySlider->setTickPosition(QSlider::TicksLeft);
        connect(decaySlider, SIGNAL(valueChanged(int)), this, SLOT(decaySliderValueChanged(int)));

        sustainSlider = new QSlider(Qt::Vertical);
        sustainSlider->setMinimum(0);
        sustainSlider->setMaximum(100);
        sustainSlider->setSingleStep(1);
        sustainSlider->setTickPosition(QSlider::TicksLeft);
        connect(sustainSlider, SIGNAL(valueChanged(int)), this, SLOT(sustainSliderValueChanged(int)));

        releaseSlider = new QSlider(Qt::Vertical);
        releaseSlider->setMinimum(100);
        releaseSlider->setMaximum(4000);
        releaseSlider->setSingleStep(100);
        releaseSlider->setTickPosition(QSlider::TicksLeft);
        connect(releaseSlider, SIGNAL(valueChanged(int)), this, SLOT(releaseSliderValueChanged(int)));

        hBox = new QHBoxLayout;
        hBox->addWidget(attackSlider);
        hBox->addWidget(decaySlider);
        hBox->addWidget(sustainSlider);
        hBox->addWidget(releaseSlider);

        setLayout(hBox);
    }

    void ADSRSettingsWidget::attackSliderValueChanged(int value) {
        emit attackValueChanged(value);
    }

    void ADSRSettingsWidget::decaySliderValueChanged(int value) {
        emit decayValueChanged(value);
    }

    void ADSRSettingsWidget::sustainSliderValueChanged(int value) {
        emit sustainValueChanged(value);
    }

    void ADSRSettingsWidget::releaseSliderValueChanged(int value) {
        emit releaseValueChanged(value);
    }
}