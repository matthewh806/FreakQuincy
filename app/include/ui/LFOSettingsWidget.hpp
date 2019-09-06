#ifndef LFOSETTINGSWIDGET_HPP
#define LFOSETTINGSWIDGET_HPP

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QCheckBox>

#include "ui/QFoldableWidget.hpp"
#include "ui/WaveformSelectorWidget.hpp"
#include "ui/QDoubleDial.hpp"

#include "engine/LFO.hpp"

namespace ui {
    class LFOSettingsWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            LFOSettingsWidget(QWidget *parent = nullptr);
            ~LFOSettingsWidget();

            void setOscType(engine::WaveTypes type);

            // void setFree(bool free);
            void setFrequency(float freq);
            void setDestination(engine::Destinations dest);
            void setBypassState(bool bypass);
            void setModDepth(int depth);
            
            signals:
                void oscTypeChanged(int);
                void frequencyChanged(double);
                void destinationChanged(int);
                void bypassToggled(int);
                void depthSliderValueChanged(double);

            private:
                void setup();

                QVBoxLayout *vBox;
                WaveformSelectorWidget *waveformSelector;
                QDoubleSpinBox *frequencySpinBox;
                QCheckBox *bypassCheckBox;
                QDoubleDial *depthDial;
                QFrame *rhsWidget;

    };
}

#endif