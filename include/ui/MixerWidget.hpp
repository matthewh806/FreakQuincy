#ifndef MIXERWIDGET_HPP
#define MIXERWIDGET_HPP

#include <map>

#include <QGroupBox>
#include <QVBoxLayout> 
#include <QDial>

namespace ui {
    class MixerWidget : public QGroupBox {
        Q_OBJECT

        public:
            MixerWidget(QWidget *parent = nullptr);
            ~MixerWidget();

            void setMixValue(int id, int v);

        signals:
            void mixValChanged(int id, int v);
        
        private:
            void setup();
            QDial* createMixerDial(int id);
            std::map<int, QDial*> mixDials;
    };
}

#endif