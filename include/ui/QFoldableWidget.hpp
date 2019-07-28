#ifndef QFOLDABLEWIDGET_HPP
#define QFOLDABLEWIDGET_HPP

/* 
    Code for this widget is mostly stolen from: https://github.com/OPM/ResInsight
        QMinimizePanel.h
        QMinimizePanel.cpp
*/ 

#include <QWidget>
#include <QFrame>
#include <QSize>
#include <QPushButton>
#include <QString>
#include <QLabel>

namespace ui {
    class QFoldableWidget : public QWidget {
        Q_OBJECT

        public:
            explicit QFoldableWidget(QWidget* parent = 0);
            explicit QFoldableWidget(const QString &title, QWidget* parent = 0);
            ~QFoldableWidget();

            QFrame* contentFrame() { return m_contentFrame; }
            void setTitle(const QString& title);

            virtual QSize minimumSizeHint() const override;

        public slots:
            void setFolded(bool isFolded);
            void toggleFolded();

        protected:
            QFrame *m_titleFrame;
            QLabel *m_titleLabel;
            QPushButton *m_foldButton;
            QFrame *m_contentFrame;

            virtual void resizeEvent(QResizeEvent *event) override;
            virtual bool event(QEvent *event) override;

        private:
            void initialize(const QString &title);
    };
}

#endif