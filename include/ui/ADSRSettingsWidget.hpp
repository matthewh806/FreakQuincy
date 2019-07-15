#ifndef ADSRSETTINGSWINDOW_hpp
#define ADSRSETTINGSWINDOW_hpp

#include <QGroupBox>
#include <QSlider>
#include <QHBoxLayout>

namespace ui {
    // TODO: Make a custom slider to allow for non linear scaling

    class ADSRSettingsWidget : public QGroupBox {
        Q_OBJECT

        public: 
            ADSRSettingsWidget(QWidget *parent = nullptr);
            ~ADSRSettingsWidget();

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