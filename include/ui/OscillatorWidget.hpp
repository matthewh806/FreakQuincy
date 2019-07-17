#ifndef OSCILLATORWIDGET_hpp
#define OSCILLATORWIDGET_hpp

#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>

#include "engine/WaveForm.hpp"

namespace ui {
    class OscillatorWidget : public QGroupBox {
        Q_OBJECT

        public:
            OscillatorWidget(QWidget *parent = nullptr);
            ~OscillatorWidget();

            void setOscType(engine::WaveTypes type);

        private slots:
            void toggleSin(bool checked);
            void toggleTri(bool checked);
            void toggleSaw(bool checked);
            void toggleSqu(bool checked);
        
        signals:
            void oscTypeChanged(int type);

        private:
            void setup();

            QVBoxLayout *vBox;
            QRadioButton *sinButton, *triButton, *sawButton, *squButton;

    };
}


#endif