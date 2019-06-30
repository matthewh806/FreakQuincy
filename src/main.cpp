#include <QApplication>
#include <memory>
#include "EngineUiIntermediary.hpp"


int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    new EngineUiIntermediary();
    return a.exec();
}