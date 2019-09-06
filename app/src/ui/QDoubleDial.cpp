#include "ui/QDoubleDial.hpp"

#include <QPainter>
#include <QResizeEvent>

namespace ui {
    void QDoubleDial::paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setBackgroundMode(Qt::OpaqueMode);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(painter.background());

        QPen textPen = painter.pen();
        painter.setPen(QPen(Qt::NoPen));
        painter.drawEllipse(0, 0, QDial::height(), QDial::height());

        painter.setPen(textPen);
        painter.drawText(*m_valueRect, Qt::AlignCenter, m_valueString);
        painter.drawText(*m_textRect, Qt::AlignHCenter | Qt::AlignBottom, m_text);

        painter.setPen(*m_arcPen);
        painter.drawArc(*m_arcRect, m_startAngle, m_angleSpan);
    }

    void QDoubleDial::resizeEvent(QResizeEvent* event) {
        QDial::setMinimumSize(event->size());
        
        double w = QDial::width() - (2 * m_arcWidth);
        double h = w / 2;

        *m_textRect = QRectF(m_arcWidth, h, w, h);
        *m_valueRect = QRectF(m_arcWidth, h, w, h);

        *m_arcRect = QRectF(
            m_arcWidth / 2,
            m_arcWidth / 2,
            QDial::width() - m_arcWidth,
            QDial::height() - m_arcWidth
        );
    }

    void QDoubleDial::notifyValueChanged(int value) {
        double val = value / (double)m_multi;

        emit doubleValueChanged(val);

        double ratio = QDial::value() / (double)QDial::maximum();
        m_angleSpan = m_maximumAngleSpan * ratio;
        m_valueString = QString::number(val);
    }
}