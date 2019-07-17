#ifndef MASTERSETTINGS_hpp
#define MASTERSETTINGS_hpp

#include <QGroupBox>
#include <QVBoxLayout>
#include <QDial>

namespace ui {
    class MasterSettingsWidget : public QGroupBox {
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