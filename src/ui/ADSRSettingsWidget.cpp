#include <Qt>
#include "ui/ADSRSettingsWidget.hpp"

namespace ui {
    ADSRSettingsWidget::ADSRSettingsWidget(QWidget *parent) {
        setTitle("ADSR");

        setup();
    }

    ADSRSettingsWidget::~ADSRSettingsWidget() {
    }

    void ADSRSettingsWidget::setValues(int a, int d, int s, int r) {
        attackSlider->setValue(a);
        decaySlider->setValue(d);
        sustainSlider->setValue(s);
        releaseSlider->setValue(r);
    }

    void ADSRSettingsWidget::setup() {
        
        QVBoxLayout *attackVBox = new QVBoxLayout;
        QLabel *attackLabel = new QLabel(tr("Attack"));
        attackSlider = new QSlider(Qt::Vertical);
        attackSlider->setMinimum(TIME_MIN);
        attackSlider->setMaximum(TIME_MAX);
        attackSlider->setSingleStep(TIME_STEP);
        attackSlider->setTickPosition(QSlider::TicksLeft);
        attackSlider->setTickInterval(TIME_TICK_INTERVAL);
        connect(attackSlider, SIGNAL(valueChanged(int)), this, SLOT(attackSliderValueChanged(int)));
        attackVBox->addWidget(attackSlider);
        attackVBox->addWidget(attackLabel);

        QVBoxLayout *decayVBox = new QVBoxLayout;
        QLabel *decayLabel = new QLabel(tr("Decay"));
        decaySlider = new QSlider(Qt::Vertical);
        decaySlider->setMinimum(TIME_MIN);
        decaySlider->setMaximum(TIME_MAX);
        decaySlider->setSingleStep(TIME_STEP);
        decaySlider->setTickPosition(QSlider::TicksLeft);
        decaySlider->setTickInterval(TIME_TICK_INTERVAL);
        connect(decaySlider, SIGNAL(valueChanged(int)), this, SLOT(decaySliderValueChanged(int)));
        decayVBox->addWidget(decaySlider);
        decayVBox->addWidget(decayLabel);

        QVBoxLayout *sustainVBox = new QVBoxLayout;
        QLabel *sustainLabel = new QLabel(tr("Sustain"));
        sustainSlider = new QSlider(Qt::Vertical);
        sustainSlider->setMinimum(SUSTAIN_MIN);
        sustainSlider->setMaximum(SUSTAIN_MAX);
        sustainSlider->setSingleStep(SUSTAIN_STEP);
        sustainSlider->setTickPosition(QSlider::TicksLeft);
        sustainSlider->setTickInterval(SUSTAIN_TICK_INTERVAL);
        connect(sustainSlider, SIGNAL(valueChanged(int)), this, SLOT(sustainSliderValueChanged(int)));
        sustainVBox->addWidget(sustainSlider);
        sustainVBox->addWidget(sustainLabel);

        QVBoxLayout *releaseVBox = new QVBoxLayout;
        QLabel *releaseLabel = new QLabel(tr("Release"));
        releaseSlider = new QSlider(Qt::Vertical);
        releaseSlider->setMinimum(TIME_MIN);
        releaseSlider->setMaximum(TIME_MAX);
        releaseSlider->setSingleStep(TIME_STEP);
        releaseSlider->setTickPosition(QSlider::TicksLeft);
        releaseSlider->setTickInterval(TIME_TICK_INTERVAL);
        connect(releaseSlider, SIGNAL(valueChanged(int)), this, SLOT(releaseSliderValueChanged(int)));
        releaseVBox->addWidget(releaseSlider);
        releaseVBox->addWidget(releaseLabel);

        hBox = new QHBoxLayout;
        hBox->addLayout(attackVBox);
        hBox->addLayout(decayVBox);
        hBox->addLayout(sustainVBox);
        hBox->addLayout(releaseVBox);

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