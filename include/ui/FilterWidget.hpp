#ifndef FILTERWIDGET_HPP
#define FILTERWIDGET_HPP

#include "ui/QFoldableWidget.hpp"

namespace ui {
    class FilterWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            FilterWidget(QWidget *parent = nullptr);
            ~FilterWidget();

        private:
            void setup();
    };
}

#endif