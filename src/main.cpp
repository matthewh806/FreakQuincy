#include <QApplication>
#include <memory>
#include "ui/EngineUiIntermediary.hpp"

// TODO:: Logging library
int main(   int argc, char * argv[])
{
    QApplication a(argc, argv);
    new ui::EngineUiIntermediary();
    return a.exec();
}