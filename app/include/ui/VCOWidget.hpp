#ifndef VCOWIDGET_HPP
#define VCOWIDGET_HPP

#include <QGroupBox>
#include <QString>

#include "ui/WaveformSelectorWidget.hpp"
#include "ui/QDoubleDial.hpp"

#include "engine/WaveForm.hpp"

namespace ui {
    class VCOWidget : public QGroupBox {
        Q_OBJECT
        
        public:
            VCOWidget(QWidget *parent = nullptr);
            VCOWidget(const QString &title, QWidget *parent = nullptr);
            ~VCOWidget();

            void setOscType(engine::WaveTypes type);
        
        signals:
            void oscTypeChanged(int type);
            void oscFineTuneValChanged(double val);
            void oscPhaseOffsetValChanged(double val);

        private:
            void setup();

            QVBoxLayout *vBox;
            WaveformSelectorWidget *waveformSelector;
            QDoubleDial *fineTuneDial;
            QDoubleDial *phaseOffsetDial;
    };
}

#endif