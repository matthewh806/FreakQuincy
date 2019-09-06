#ifndef FILTERWIDGET_HPP
#define FILTERWIDGET_HPP

#include "ui/QFoldableWidget.hpp"
#include "ui/QDoubleDial.hpp"

namespace ui {
    class FilterWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            FilterWidget(QWidget *parent = nullptr);
            ~FilterWidget();

            void setCutoff(double cutoff) {
                cutoffDial->setValue(cutoff);
            }
            void setResonance(double res) {
                resonanceDial->setValue(res);
            }

            signals:
                // void filterTypeChanged(int);
                void cutoffChanged(double);
                void resonanceChanged(double);

        private:
            void setup();

            QDoubleDial *cutoffDial;
            QDoubleDial *resonanceDial;
    };
}

#endif