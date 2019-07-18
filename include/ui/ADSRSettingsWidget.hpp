#ifndef ADSRSETTINGSWINDOW_hpp
#define ADSRSETTINGSWINDOW_hpp

#include <QGroupBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace ui {
    // TODO: Make a custom slider to allow for non linear scaling

    class ADSRSettingsWidget : public QGroupBox {
        Q_OBJECT

        public: 
            ADSRSettingsWidget(QWidget *parent = nullptr);
            ~ADSRSettingsWidget();

            // These are common between the time based ADSR sliders
            const int TICK_COUNT = 20;

            const int TIME_MIN = 50;
            const int TIME_MAX = 4000;
            const int TIME_STEP = 100;
            const int TIME_TICK_INTERVAL = (TIME_MAX - TIME_MIN) / TICK_COUNT;

            const int SUSTAIN_MIN = 0;
            const int SUSTAIN_MAX = 100;
            const int SUSTAIN_STEP = 1;
            const int SUSTAIN_TICK_INTERVAL = (SUSTAIN_MAX - SUSTAIN_MIN) / TICK_COUNT;

            void setValues(int a, int d, int s, int r);

        signals:
            void attackValueChanged(int);
            void decayValueChanged(int);
            void sustainValueChanged(int);
            void releaseValueChanged(int);

        private slots:
            void attackSliderValueChanged(int);
            void decaySliderValueChanged(int);
            void sustainSliderValueChanged(int);
            void releaseSliderValueChanged(int);

        private:
            void setup();

            QHBoxLayout *hBox;
            QSlider *attackSlider;
            QSlider *decaySlider;
            QSlider *sustainSlider;
            QSlider *releaseSlider;
    };
}

#endif