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

    void GeneralSettingsWidget::initializeMidiInOptions(std::map<int, std::string> midiInputOptions) {
        for(auto const& x : midiInputOptions) {
            midiInputComboBox->insertItem(x.first, QString::fromStdString(x.second));
        }
    }

    void GeneralSettingsWidget::initializeAudioOutputOptions(std::map<int, std::string> outputDevices) {
        for(auto const& x : outputDevices) {
            audioOutputComboBox->insertItem(x.first, QString::fromStdString(x.second));
        }
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
        
        QLabel *midiInputLabel = new QLabel(tr("Midi Input device"));
        midiInputComboBox = new QComboBox;
        connect(midiInputComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), 
            [=](int val) { this->emit midiInputChanged(val); });

        QLabel *audioOutputLabel = new QLabel(tr("Audio Output Device"));
        audioOutputComboBox = new QComboBox;
        connect(audioOutputComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [=](int val) {this->emit audioOutputChanged(val);});

        vBox = new QVBoxLayout;
        vBox->addWidget(sampleRateLabel);
        vBox->addWidget(sampleRateSpinBox);
        vBox->addWidget(legatoCheckBox);
        vBox->addWidget(midiInputLabel);
        vBox->addWidget(midiInputComboBox);
        vBox->addWidget(audioOutputLabel);
        vBox->addWidget(audioOutputComboBox);

        this->contentFrame()->setLayout(vBox);
    }
}