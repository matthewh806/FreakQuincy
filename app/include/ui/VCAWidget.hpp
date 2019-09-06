#ifndef VCAWIDGET_hpp
#define VCAWIDGET_hpp

#include <QVBoxLayout>

#include "ui/ADSRSettingsWidget.hpp"
#include "ui/QFoldableWidget.hpp"

namespace ui {
    class VCAWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            VCAWidget(QWidget *parent = nullptr);
            ~VCAWidget(); 

            void initialize(int a, int d, int s, int r) { adsrWidget->setValues(a, d, s, r);};

        signals:
            void ampAttackValChanged(int v);
            void ampDecayValChanged(int v);
            void ampSustainValChanged(int v);
            void ampReleaseValChanged(int v);

        private:
            void setup();

            QVBoxLayout *vBox;
            ADSRSettingsWidget *adsrWidget;

    };
}

#endif