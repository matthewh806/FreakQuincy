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

    void GeneralSettingsWidget::sampleRateSpinBoxValChanged(int rate) {
        emit sampleRateChanged(rate);
    }

    void GeneralSettingsWidget::legatoCheckBoxStateChanged(int state) {
        emit legatoToggled(state == 0 ? false : true);
    }

    void GeneralSettingsWidget::setup() {
        QLabel *sampleRateLabel = new QLabel(tr("Sample Rate"));

        sampleRateSpinBox = new QSpinBox;
        sampleRateSpinBox->setRange(1000, 44100);
        sampleRateSpinBox->setSingleStep(1000);
        connect(sampleRateSpinBox, SIGNAL(valueChanged(int)), this, SLOT(sampleRateSpinBoxValChanged(int)));
        sampleRateSpinBox->setValue(engine::AudioSettings::getSampleRate());

        legatoCheckBox = new QCheckBox(tr("Legato"), this);
        connect(legatoCheckBox, SIGNAL(stateChanged(int)), this, SLOT(legatoCheckBoxStateChanged(int)));
        legatoCheckBox->setChecked(engine::AudioSettings::isLegatoEnabled());

        vBox = new QVBoxLayout;
        vBox->addWidget(sampleRateLabel);
        vBox->addWidget(sampleRateSpinBox);
        vBox->addWidget(legatoCheckBox);

        setLayout(vBox);
    }
}