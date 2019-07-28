#include <QLabel>

#include "ui/LFOSettingsWidget.hpp"

namespace ui {
    LFOSettingsWidget::LFOSettingsWidget(QWidget *parent) {
        setTitle("LFO");

        setup();
    }

    LFOSettingsWidget::~LFOSettingsWidget() {

    }

    void LFOSettingsWidget::setOscType(engine::WaveTypes type) {
        waveformSelector->setOscType(type);
    }

    void LFOSettingsWidget::setFrequency(float freq) {
        frequencySpinBox->setValue((double)freq);
    }

    void LFOSettingsWidget::setDestination(engine::Destinations dest) {
        switch(dest) {
            case engine::Destinations::PITCH:
                pitchDestButton->toggle();
                break;
            case engine::Destinations::VOLUME:
                volDestButton->toggle();
                break;
            default:
                break;
        }
    }

    void LFOSettingsWidget::setup() {
        waveformSelector = new WaveformSelectorWidget();
        connect(
            waveformSelector, &WaveformSelectorWidget::oscTypeToggled, 
            this, [=](int type) { this->emit oscTypeChanged(type); }
        );

        volDestButton = new QRadioButton(tr("volume"));
        connect(
            this, &LFOSettingsWidget::toggled, 
            this, [=](bool checked) { 
                if(!checked)
                    return;
                this->emit setDestination(engine::Destinations::VOLUME);
            }
        );

        pitchDestButton = new QRadioButton(tr("pitch"));
        connect(
            this, &LFOSettingsWidget::toggled, 
            this, [=](bool checked) {
                if(!checked)
                    return;
                this->emit setDestination(engine::Destinations::PITCH);
            }
        );

        QLabel *frequencyLabel = new QLabel(tr("Frequency"));
        frequencySpinBox = new QDoubleSpinBox;
        frequencySpinBox->setRange(0.0625, 100);
        frequencySpinBox->setSingleStep(1.0);

        void (QDoubleSpinBox::*freqSignal)(double) = &QDoubleSpinBox::valueChanged;
        connect(
            frequencySpinBox, freqSignal,
            this, [=](double val) {
                this->emit frequencyChanged(val);
            }
        );
        frequencySpinBox->setValue(0.0);

        vBox = new QVBoxLayout;
        vBox->addWidget(waveformSelector);
        vBox->addWidget(volDestButton);
        vBox->addWidget(pitchDestButton);
        vBox->addWidget(frequencyLabel);
        vBox->addWidget(frequencySpinBox);
        
        setLayout(vBox);
    }
}