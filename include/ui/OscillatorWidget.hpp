#ifndef OSCILLATORWIDGET_hpp
#define OSCILLATORWIDGET_hpp

#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>

#include "ui/WaveformSelectorWidget.hpp"
#include "engine/WaveForm.hpp"

namespace ui {
    class OscillatorWidget : public QGroupBox {
        Q_OBJECT

        public:
            OscillatorWidget(QWidget *parent = nullptr);
            ~OscillatorWidget();

            void setOscType(engine::WaveTypes type);
        
        signals:
            void oscTypeChanged(int type);            

        private:
            void setup();

            QVBoxLayout *vBox;
            WaveformSelectorWidget *waveformSelector;
    };
}


#endif