#ifndef OSCILLATORWIDGET_hpp
#define OSCILLATORWIDGET_hpp

#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>

namespace ui {
    class OscillatorWidget : public QGroupBox {
        Q_OBJECT

        public:
            OscillatorWidget(QWidget *parent = nullptr);
            ~OscillatorWidget();

        private:
            void setup();

            QVBoxLayout *vBox;
            QRadioButton *sinButton, *squButton;

    };
}


#endif