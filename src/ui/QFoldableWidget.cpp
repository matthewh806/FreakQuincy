
#include <QApplication>
#include <QResizeEvent>

#include "ui/QFoldableWidget.hpp"

namespace ui {

    QFoldableWidget::QFoldableWidget(QWidget *parent) {
        this->initialize("");
    }

    QFoldableWidget::QFoldableWidget(const QString &title, QWidget *parent) {
        this->initialize(title);
    }

    QFoldableWidget::~QFoldableWidget() {}

    void QFoldableWidget::initialize(const QString &title) {
        m_titleFrame = new QFrame(this);
        m_titleFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
        m_titleFrame->setAutoFillBackground(true);

        m_titleLabel = new QLabel(title, m_titleFrame);
        m_titleLabel->setPalette(QApplication::palette());

        m_foldButton = new QPushButton(m_titleFrame);
        m_foldButton->setFlat(true);
        
        m_contentFrame = new QFrame(this);
        m_contentFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        m_contentFrame->setAutoFillBackground(true);

        connect(m_foldButton, SIGNAL(clicked()), this, SLOT(toggleFolded()));
    }

    void QFoldableWidget::setTitle(const QString& title) {
        m_titleLabel->setText(title);
    }

    void QFoldableWidget::setFolded(bool isFolded) {
        // TODO: update button state.
        m_contentFrame->setVisible(!isFolded);
        this->QWidget::updateGeometry();
    }

    void QFoldableWidget::toggleFolded() {
        setFolded(!m_contentFrame->isVisible());
    }

    QSize QFoldableWidget::minimumSizeHint() const {
        QSize labelSize = m_titleLabel->sizeHint();
        QSize titleBarHint = labelSize + QSize(labelSize.height() + 8, 8);

        if(m_contentFrame->isVisible()) {
            QSize titleBarMin(0, labelSize.height() + 8);
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
        int labelHeight = m_titleLabel->sizeHint().height();
        int titleHeight = labelHeight + 8;
        int buttonSize = titleHeight - 2;

        m_titleFrame->setGeometry(0, 0, width, titleHeight);
        m_titleLabel->setGeometry(4, titleHeight-labelHeight-4, width - buttonSize - 1, labelHeight);
        m_foldButton->setGeometry(width-buttonSize - 1, 1, buttonSize, buttonSize);

        m_contentFrame->setGeometry(0, titleHeight-1, width, height - titleHeight - 1);
    }

    bool QFoldableWidget::event(QEvent *event) {
            if(event->type() == QEvent::LayoutRequest)
                this->QWidget::updateGeometry();
            
            return this->QWidget::event(event);
    }
}