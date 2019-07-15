#ifndef GENERALSETTINGS_hpp
#define GENERALSETTINGS_hpp

#include <QGroupBox>
#include <QHBoxLayout>
#include <QSpinBox>

namespace ui {
    class GeneralSettingsWidget : public QGroupBox {
        Q_OBJECT

        public:
            GeneralSettingsWidget(QWidget *parent = nullptr);
            ~GeneralSettingsWidget();

        signals:
            void sampleRateChanged(int);

        private slots:
            void sampleRateSpinBoxValChanged(int);

        private:
            void setup();

            QVBoxLayout *vBox;
            QSpinBox *sampleRateSpinBox;
    };
}

#endif