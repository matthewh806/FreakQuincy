#include <Qt>
#include <QLabel>

#include "ui/MasterSettingsWidget.hpp"
#include "engine/AudioSettings.hpp"

namespace ui {
    MasterSettingsWidget::MasterSettingsWidget(QWidget *parent) {
        setTitle("Master");

        setup();
    }

    MasterSettingsWidget::~MasterSettingsWidget() {
        
    }

    void MasterSettingsWidget::setup() {
        volumeDial = new QDial();
        volumeDial->setMinimum(0);
        volumeDial->setMaximum(100);
        volumeDial->setSingleStep(10);
        volumeDial->setValue((int)(engine::AudioSettings::getMasterVolume() * 100)); // TODO: Handle this elsewhere
        volumeDial->setNotchesVisible(true);
        connect(volumeDial, SIGNAL(valueChanged(int)), this, SLOT(volumeSliderValueChanged(int)));

        QLabel *volumeLabel = new QLabel(tr("volume"));
        volumeLabel->setAlignment(Qt::AlignHCenter);

        vBox = new QVBoxLayout;
        vBox->addWidget(volumeDial);
        vBox->addWidget(volumeLabel);
        this->contentFrame()->setLayout(vBox);
    }

    void MasterSettingsWidget::volumeSliderValueChanged(int v) {
        emit masterVolumeChanged((float)v/100.0);
    }
}