#include <QApplication>
#include <main_window.h>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(600, 420);
    w.setWindowTitle("FreakQuency");
    w.show();

    return a.exec();
}