#include <QApplication>
#include <main_window.h>
#include <memory>
#include "AudioEngine.hpp"
#include "wave_form.h"

std::shared_ptr<WaveForm> p_wave;
std::unique_ptr<AudioEngine> engine;

int main(int argc, char * argv[])
{
    p_wave = std::make_shared<WaveForm>();
    engine = std::unique_ptr<AudioEngine>(new AudioEngine(p_wave));

    QApplication a(argc, argv);
    
    MainWindow w;
    w.setWave(p_wave);
    w.resize(600, 420);
    w.setWindowTitle("FreakQuency");
    w.show();

    return a.exec();
}