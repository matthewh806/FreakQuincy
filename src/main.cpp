#include <QApplication>
#include <main_window.h>
#include <memory>
#include "RtAudio.h"
#include "AudioSettings.hpp"
#include "wave_form.h"

float volume = 0.2f;
std::shared_ptr<WaveForm> p_wave;
RtAudio dac(RtAudio::MACOSX_CORE);

void play(double *output) {
    output[0] = volume * p_wave->get_inst_waveOutput();
    output[1] = output[0];
}

int routing(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData) {
    unsigned int i, j;
    double *buffer = (double *)outputBuffer;
    double *lastValues = (double *) userData;

    if(status)
        std::cout << "Stream underflow detected!" << std::endl;

    for(i = 0; i < nBufferFrames; i++) {
        play(lastValues);
        for(j = 0; j < 2; j++) {
            *buffer++ = lastValues[j];
        }
    }

    return 0;
}

void setupAudioOutput() {
    if(dac.getDeviceCount() < 1) {
        std::cout << "No audio devices found!" << std::endl;
        return;
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = AudioSettings::getChannels();
    parameters.firstChannel = 0;

    unsigned int bufferFrames = AudioSettings::getbufferSize();
    unsigned int sampleRate = AudioSettings::getSampleRate();
    std::vector<double> data(AudioSettings::getChannels(), 0);

    std::cout << dac.getDeviceInfo(parameters.deviceId).name << std::endl;
    std::cout << dac.getDeviceInfo(parameters.deviceId).preferredSampleRate << std::endl;

    try {
        dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                       48000, &bufferFrames, &routing, (void *)&(data[0]));
        dac.startStream();
    } catch(RtAudioError& e) {
        std::cout << e.getMessage() << std::endl;
        return;
    }
}


int main(int argc, char * argv[])
{
    setupAudioOutput();
    p_wave = std::make_shared<WaveForm>();

    QApplication a(argc, argv);
    
    MainWindow w;
    w.setWave(p_wave);
    w.resize(600, 420);
    w.setWindowTitle("FreakQuency");
    w.show();

    std::cout << dac.isStreamOpen() << std::endl;

    return a.exec();
}