#ifndef QDOUBLEDIAL_HPP
#define QDOUBLEDIAL_HPP

#include <math.h>

#include <iostream>

#include <QDial>
#include <QSharedPointer>
#include <QRectF>
#include <QColor>
#include <QPen>

/*
* Layout specific implementation mostly comes from this blog post:
* http://thecodeinn.blogspot.com/2015/03/customizing-qdials-in-qt-part-2.html
*/

namespace ui {

    class QDoubleDial : public QDial {
        Q_OBJECT

        Q_PROPERTY(QString arcColor READ getArcColor WRITE setArcColor)

        Q_PROPERTY(double arcWidth READ getArcWidth WRITE setArcWidth)

        public:
            explicit QDoubleDial(QWidget* parent = nullptr);

            QDoubleDial(const QString& text, QWidget *parent = nullptr, int mag = 1) : 
            QDial(parent),
            m_text(text),
            m_arcRect(new QRectF),
            m_textRect(new QRectF),
            m_valueRect(new QRectF),
            m_arcColor(new QColor),
            m_arcPen(new QPen)
            {
                this->m_multi = pow(10, mag);

                QDial::setCursor(Qt::PointingHandCursor);

                connect(this, &QDial::valueChanged,
                    this, &QDoubleDial::notifyValueChanged
                );

                setMinimumSize(100, 100);
                setMaximumSize(100, 100); 
                setMaximumAngle(-360);

                QSizePolicy p(sizePolicy());
                p.setHorizontalPolicy( QSizePolicy::Preferred );
                p.setVerticalPolicy( QSizePolicy::Preferred );
                p.setHeightForWidth(true);
                setSizePolicy(p);
            };

            ~QDoubleDial() {};

            QSize sizeHint() const override {
                return QSize(100, 100);
            }

            QSize minimumSizeHint() const override {
                return QSize(100, 100);
            }

            int heightForWidth(int w) const override {
                return w;
            }

            void setArcColor(const QString& color) {
                m_arcColor->setNamedColor(color);
                m_arcPen->setColor(*m_arcColor);
            }

            QString getArcColor() const {
                return m_arcColor->name();
            }

            void setStartAngle(double angle) {
                m_startAngle = angle * 16;
            }

            double getStartAngle() const {
                return m_startAngle / 16;
            }

            void setMaximumAngle(double angle) {
                m_maximumAngleSpan = angle * 16;
            }

            double getMaximumAngle() const {
                return m_maximumAngleSpan / 16;
            }

            void setArcWidth(double px) {
                m_arcWidth = px;
                
                *m_arcRect = QRectF(
                    m_arcWidth / 2,
                    m_arcWidth / 2,
                    QDial::width() - m_arcWidth,
                    QDial::height() - m_arcWidth
                );

                m_arcPen->setWidth(m_arcWidth);
            }

            double getArcWidth() const {
                return m_arcWidth;
            }

            void setText(const QString& text) {
                m_text = text;
            }

            QString getText() const {
                return m_text;
            }

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

                double ratio = QDial::value() / (double)QDial::maximum();
                setStartAngle(m_maximumAngleSpan * ratio);
            }

            void setMagnitude(int mag) {
                this->m_multi = pow(10, mag);
            }

        signals:
            void doubleValueChanged(double value);

        public slots:
            void notifyValueChanged(int value);

        private:
            virtual void paintEvent(QPaintEvent*) override;
            virtual void resizeEvent(QResizeEvent* event) override;

            int m_multi;

            double m_maximumAngleSpan;
            double m_startAngle;
            double m_arcWidth;
            double m_angleSpan;

            QString m_valueString;
            QString m_text;

            QSharedPointer<QRectF> m_arcRect;
            QSharedPointer<QRectF> m_textRect;
            QSharedPointer<QRectF> m_valueRect;
            QSharedPointer<QColor> m_arcColor;
            QSharedPointer<QPen> m_arcPen;
    };
}

#endif