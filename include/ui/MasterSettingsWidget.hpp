#ifndef MASTERSETTINGS_hpp
#define MASTERSETTINGS_hpp

#include <QVBoxLayout>

#include "ui/QFoldableWidget.hpp"
#include "ui/QDoubleDial.hpp"

namespace ui {
    class MasterSettingsWidget : public QFoldableWidget {
        Q_OBJECT

        public:
            MasterSettingsWidget(QWidget *parent = nullptr);
            ~MasterSettingsWidget();

        signals:
            void masterVolumeChanged(float);

        private:
            void setup();

            QVBoxLayout *vBox;
            QDoubleDial *volumeDial;
    };
}

#endif