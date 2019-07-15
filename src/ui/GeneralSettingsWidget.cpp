#include <QLabel>

#include "ui/GeneralSettingsWidget.hpp"
#include "engine/AudioSettings.hpp"


namespace ui {
    GeneralSettingsWidget::GeneralSettingsWidget(QWidget *parent) {
        setTitle("Settings");

        setup();
    }

    GeneralSettingsWidget::~GeneralSettingsWidget() {

    }

    void GeneralSettingsWidget::setup() {
        QLabel *sampleRateLabel = new QLabel(tr("Sample Rate"));

        sampleRateSpinBox = new QSpinBox;
        sampleRateSpinBox->setRange(1000, 44100);
        sampleRateSpinBox->setSingleStep(1000);
        sampleRateSpinBox->setValue(engine::AudioSettings::getSampleRate());

        vBox = new QVBoxLayout;
        vBox->addWidget(sampleRateLabel);
        vBox->addWidget(sampleRateSpinBox);

        setLayout(vBox);
    }
}