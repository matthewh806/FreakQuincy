#ifndef OSCILLATORWIDGET_hpp
#define OSCILLATORWIDGET_hpp

#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ui/QFoldableWidget.hpp"
#include "ui/VCOWidget.hpp"
#include "ui/MixerWidget.hpp"

namespace ui {
    class OscillatorWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            OscillatorWidget(QWidget *parent = nullptr);
            ~OscillatorWidget();

            VCOWidget *vco1, *vco2;
            MixerWidget *mixerWidget;

        private:
            void setup();
    };
}


#endif