#ifndef GENERALSETTINGS_hpp
#define GENERALSETTINGS_hpp

#include <QHBoxLayout>
#include <QSpinBox>
#include <QCheckBox>

#include <ui/QFoldableWidget.hpp>

namespace ui {
    class GeneralSettingsWidget : public QFoldableWidget {
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