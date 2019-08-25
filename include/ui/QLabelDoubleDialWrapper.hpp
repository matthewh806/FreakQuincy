#ifndef QLABELDIALWRAPPER_HPP
#define QLABELDIALWRAPPER_HPP

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

#include "ui/QDoubleDial.hpp"

namespace ui {
    // TODO: Option to set label above / below
    class QLabelDoubleDialWrapper : public QFrame {
        Q_OBJECT

        public:
            QLabelDoubleDialWrapper(QWidget *parent = nullptr, QString dialLabel = tr(""), int dialMagnitude=1) : QFrame(parent) {
                label = new QLabel(dialLabel, this);
                label->setAlignment(Qt::AlignHCenter);

                dial = new QDoubleDial(this, dialMagnitude);

                QVBoxLayout *vBox = new QVBoxLayout;
                vBox->addWidget(dial);
                vBox->addWidget(label);

                this->setLayout(vBox);
            }

            ~QLabelDoubleDialWrapper() {};

            QDoubleDial *dial;
            QLabel *label;
    };
}

#endif