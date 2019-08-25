#ifndef QDOUBLEDIAL_HPP
#define QDOUBLEDIAL_HPP

#include <math.h>
#include <QDial>

namespace ui {

    class QDoubleDial : public QDial {
        Q_OBJECT

        public:
            QDoubleDial(QWidget *parent = nullptr, int mag = 1) : QDial(parent) {
                this->m_multi = pow(10, mag);

                connect(this, SIGNAL(valueChanged(int)),
                    this, SLOT(notifyValueChanged(int))
                );
            };

            ~QDoubleDial() {};

            void setMinimum(double val) {
                QDial::setMinimum(val * this->m_multi);
            }

            void setMaximum(double val) {
                QDial::setMaximum(val * this->m_multi);
            }

            void setSingleStep(double val) {
                QDial::setSingleStep(val * this->m_multi);
            }

            void setValue(double val) {
                QDial::setValue(val * this->m_multi);
            }

            void setMagnitude(int mag) {
                this->m_multi = pow(10, mag);
            }

        signals:
            void doubleValueChanged(double value);

        public slots:
            void notifyValueChanged(int value) {
                emit doubleValueChanged(value / (double)m_multi);
        }

        private:
            int m_multi;
    };
}

#endif