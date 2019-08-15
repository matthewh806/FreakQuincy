#ifndef GENERALSETTINGS_hpp
#define GENERALSETTINGS_hpp

#include <QHBoxLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

#include <ui/QFoldableWidget.hpp>

namespace ui {
    class GeneralSettingsWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            GeneralSettingsWidget(QWidget *parent = nullptr);
            ~GeneralSettingsWidget();

            void initializeMidiInOptions(std::map<int, std::string> midiInputOptions);

        signals:
            void sampleRateChanged(int);
            void legatoToggled(bool);
            void midiInputChanged(int);

        private slots:
            void sampleRateSpinBoxValChanged(int);
            void legatoCheckBoxStateChanged(int);

        private:
            void setup();

            QVBoxLayout *vBox;
            QSpinBox *sampleRateSpinBox;
            QComboBox *midiInputComboBox;
            QCheckBox *legatoCheckBox;
    };
}

#endif