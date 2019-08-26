#include <Qt>
#include <QLabel>

#include "ui/MasterSettingsWidget.hpp"
#include "engine/AudioSettings.hpp"

namespace ui {
    MasterSettingsWidget::MasterSettingsWidget(QWidget *parent) : QFoldableWidget(parent) {
        setTitle("Master");

        setup();
    }

    MasterSettingsWidget::~MasterSettingsWidget() {
        
    }

    void MasterSettingsWidget::setup() {
        volumeDial = new QDoubleDial("Volume", this, 1);
        volumeDial->setMinimum(0.0);
        volumeDial->setMaximum(1.0);
        volumeDial->setSingleStep(0.05);
        volumeDial->setValue(engine::AudioSettings::getMasterVolume());
        volumeDial->setNotchesVisible(true);
        connect(volumeDial, &QDoubleDial::doubleValueChanged, this, 
            [=](double val) { this->emit masterVolumeChanged(val); }
        );

        vBox = new QVBoxLayout;
        vBox->addWidget(volumeDial, 0, Qt::AlignHCenter);
        this->contentFrame()->setLayout(vBox);
    }
}