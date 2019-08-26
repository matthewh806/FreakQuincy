#ifndef MIXERWIDGET_HPP
#define MIXERWIDGET_HPP

#include <map>

#include <QGroupBox>
#include <QVBoxLayout> 

#include "ui/QDoubleDial.hpp"

namespace ui {
    class MixerWidget : public QGroupBox {
        Q_OBJECT

        public:
            MixerWidget(QWidget *parent = nullptr);
            ~MixerWidget();

            void setMixValue(int id, double v);

        signals:
            void mixValChanged(int id, double v);
        
        private:
            void setup();
            QDoubleDial* createMixerDial(int id);
            std::map<int, QDoubleDial*> mixDials;
    };
}

#endif