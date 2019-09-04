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

    void LFOSettingsWidget::setBypassState(bool bypass) {
        bypassCheckBox->setChecked(bypass);
    }

    void LFOSettingsWidget::setModDepth(int depth) {
        depthDial->setValue(depth);
    }

    void LFOSettingsWidget::setDestination(engine::Destinations dest) {
        // switch(dest) {
        //     case engine::Destinations::PITCH:
        //         pitchDestButton->toggle();
        //         break;
        //     case engine::Destinations::AMP:
        //         volDestButton->toggle();
        //         break;
        //     default:
        //         break;
        // }
    }

    void LFOSettingsWidget::setup() {
        waveformSelector = new WaveformSelectorWidget();
        connect(
            waveformSelector, &WaveformSelectorWidget::oscTypeToggled, 
            this, [=](int type) { this->emit oscTypeChanged(type); }
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

        bypassCheckBox = new QCheckBox(tr("Bypass"), this);
        connect(bypassCheckBox, &QCheckBox::stateChanged, this, 
            [=](int val) { this->emit bypassToggled(val);
        });
        
        depthDial = new QDoubleDial("Depth", this, 1);
        depthDial->setMinimum(0);
        depthDial->setMaximum(1);
        depthDial->setSingleStep(0.05);
        connect(depthDial, &QDial::valueChanged, this, 
            [=](double val) { this->emit depthSliderValueChanged(val);
        });
        
        rhsWidget = new QFrame;
        vBox = new QVBoxLayout;
        vBox->addWidget(frequencyLabel);
        vBox->addWidget(frequencySpinBox);
        vBox->addWidget(depthDial, 0, Qt::AlignHCenter);
        vBox->addWidget(bypassCheckBox);
        rhsWidget->setLayout(vBox);

        QHBoxLayout *hBoxLayout = new QHBoxLayout;
        hBoxLayout->addWidget(waveformSelector);
        hBoxLayout->addWidget(rhsWidget);
        
        this->contentFrame()->setLayout(hBoxLayout);
    }
}