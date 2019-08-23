#include <QApplication>
#include <QResizeEvent>
#include <QPainter>
#include <QStyleOption>

#include "ui/QFoldableWidget.hpp"

namespace ui {

    QFoldableWidget::QFoldableWidget(QWidget *parent) : QWidget(parent) {
        this->initialize("");
        this->setAttribute(Qt::WA_StyleSheet, true);
        this->setAttribute(Qt::WA_StyleSheetTarget, true);
        this->setAttribute(Qt::WA_StyledBackground, true);
    }

    QFoldableWidget::QFoldableWidget(const QString &title, QWidget *parent) {
        this->initialize(title);
    }

    QFoldableWidget::~QFoldableWidget() {}

    void QFoldableWidget::initialize(const QString &title) {
        m_titleFrame = new QFrame(this);
        m_titleFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
        m_titleFrame->setAutoFillBackground(true);

        m_foldButton = new QPushButton(m_titleFrame);
        m_foldButton->setFlat(true);
        m_foldButton->setText(title);
        
        m_contentFrame = new QFrame(this);
        m_contentFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        m_contentFrame->setAutoFillBackground(true);

        connect(m_foldButton, SIGNAL(clicked()), this, SLOT(toggleFolded()));
    }

    void QFoldableWidget::setTitle(const QString& title) {
        m_foldButton->setText(title);
    }

    void QFoldableWidget::setFolded(bool fold) {
        m_contentFrame->setVisible(!fold);
        this->QWidget::updateGeometry();

        emit widgetFolded(this);
    }

    void QFoldableWidget::toggleFolded() {
        setFolded(m_contentFrame->isVisible());
    }

    QSize QFoldableWidget::minimumSizeHint() const {
        QSize buttonSize = m_foldButton->sizeHint();
        QSize titleBarHint = buttonSize;

        if(m_contentFrame->isVisible()) {
            QSize titleBarMin(0, buttonSize.height());
            QSize contentsMin(m_contentFrame->minimumSizeHint());
            QSize total = contentsMin.expandedTo(titleBarMin);
            total.rheight() += titleBarMin.height();
            return total;
        } else {
            return titleBarHint;
        }
    }

    void QFoldableWidget::resizeEvent(QResizeEvent *event) {
        QWidget::updateGeometry();

        int width = event->size().width();
        int height = event->size().height();
        int buttonHeight = m_foldButton->sizeHint().height();

        m_titleFrame->setGeometry(0, 0, width, buttonHeight);
        m_foldButton->setGeometry(0, 0, width, buttonHeight);

        m_contentFrame->setGeometry(0, buttonHeight-1, width, height - buttonHeight - 1);
    }

    bool QFoldableWidget::event(QEvent *event) {
            if(event->type() == QEvent::LayoutRequest)
                this->QWidget::updateGeometry();
            
            return this->QWidget::event(event);
    }

    void QFoldableWidget::paintEvent(QPaintEvent *) {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
}