#include <QApplication>
#include <QFile>
#include <memory>
#include "ui/EngineUiIntermediary.hpp"

// TODO:: Logging library
int main(   int argc, char * argv[])
{    
    QApplication a(argc, argv);

    QFile file(":ui/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll()); 
    a.setStyleSheet(styleSheet);

    new ui::EngineUiIntermediary();
    return a.exec();
}