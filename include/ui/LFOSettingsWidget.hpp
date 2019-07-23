#ifndef LFOSETTINGSWIDGET_HPP
#define LFOSETTINGSWIDGET_HPP

#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QDoubleSpinBox>

#include "ui/WaveformSelectorWidget.hpp"
#include "engine/LFO.hpp"

namespace ui {
    class LFOSettingsWidget : public QGroupBox {
        Q_OBJECT

        public:
            LFOSettingsWidget(QWidget *parent = nullptr);
            ~LFOSettingsWidget();

            void setOscType(engine::WaveTypes type);

            // void setFree(bool free);
            void setFrequency(float freq);
            void setDestination(engine::Destinations dest);
            
            signals:
                void oscTypeChanged(int);
                void frequencyChanged(double);
                void destinationChanged(int);

            private:
                void setup();

                QVBoxLayout *vBox;
                WaveformSelectorWidget *waveformSelector;
                QRadioButton *volDestButton, *pitchDestButton;
                QDoubleSpinBox *frequencySpinBox;

    };
}

#endif