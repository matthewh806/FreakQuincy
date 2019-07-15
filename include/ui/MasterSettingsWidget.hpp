#ifndef MASTERSETTINGS_hpp
#define MASTERSETTINGS_hpp

#include <QGroupBox>
#include <QVBoxLayout>

namespace ui {
    class MasterSettingsWidget : public QGroupBox {
        Q_OBJECT

        public:
            MasterSettingsWidget(QWidget *parent = nullptr);
            ~MasterSettingsWidget();
        
        private:
            void setup();
            QVBoxLayout *vBox;
    };
}

#endif