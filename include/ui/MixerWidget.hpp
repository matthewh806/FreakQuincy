#ifndef MIXERWIDGET_HPP
#define MIXERWIDGET_HPP

#include <map>

#include <QGroupBox>
#include <QVBoxLayout> 

#include "ui/QLabelDoubleDialWrapper.hpp"

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
            QLabelDoubleDialWrapper* createMixerDial(int id);
            std::map<int, QLabelDoubleDialWrapper*> mixDials;
    };
}

#endif