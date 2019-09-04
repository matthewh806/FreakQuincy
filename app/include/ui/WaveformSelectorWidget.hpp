#ifndef WAVEFORMSELECTOR_HPP
#define WAVEFORMSELECTOR_HPP

#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>

#include "engine/WaveForm.hpp"

namespace ui {
    class WaveformSelectorWidget : public QGroupBox {
        Q_OBJECT

        public:
            WaveformSelectorWidget(QWidget *parent = nullptr);
            ~WaveformSelectorWidget();

            void setOscType(engine::WaveTypes type);

        private slots:
            void toggleSin(bool checked);
            void toggleTri(bool checked);
            void toggleSaw(bool checked);
            void toggleSqu(bool checked);
        
        signals:
            void oscTypeToggled(int type);

        private:
            void setup();

            QVBoxLayout *vBox;
            QRadioButton *sinButton, *triButton, *sawButton, *squButton;

    };
}


#endif