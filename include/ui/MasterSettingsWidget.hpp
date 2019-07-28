#ifndef MASTERSETTINGS_hpp
#define MASTERSETTINGS_hpp

#include <QVBoxLayout>
#include <QDial>

#include "ui/QFoldableWidget.hpp"

namespace ui {
    class MasterSettingsWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            MasterSettingsWidget(QWidget *parent = nullptr);
            ~MasterSettingsWidget();

        signals:
            void masterVolumeChanged(float);

        private slots:
            void volumeSliderValueChanged(int);

        private:
            void setup();

            QVBoxLayout *vBox;
            QDial *volumeDial;
    };
}

#endif