#include <QApplication>
#include <QFile>
#include <memory>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "ui/EngineUiIntermediary.hpp"

auto console = spdlog::stdout_color_mt("main");

int main(   int argc, char * argv[])
{    
    spdlog::set_level(spdlog::level::debug);

    QApplication a(argc, argv);

    QFile file(":ui/stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll()); 
    a.setStyleSheet(styleSheet);

    new ui::EngineUiIntermediary();
    return a.exec();
}