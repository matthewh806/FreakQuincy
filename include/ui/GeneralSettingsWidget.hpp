#ifndef GENERALSETTINGS_hpp
#define GENERALSETTINGS_hpp

#include <QGroupBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QCheckBox>

namespace ui {
    class GeneralSettingsWidget : public QGroupBox {
        Q_OBJECT

        public:
            GeneralSettingsWidget(QWidget *parent = nullptr);
            ~GeneralSettingsWidget();

        signals:
            void sampleRateChanged(int);
            void legatoToggled(bool);

        private slots:
            void sampleRateSpinBoxValChanged(int);
            void legatoCheckBoxStateChanged(int);

        private:
            void setup();

            QVBoxLayout *vBox;
            QSpinBox *sampleRateSpinBox;
            QCheckBox *legatoCheckBox;
    };
}

#endif