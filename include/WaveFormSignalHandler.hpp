#ifndef WAVEFORMSIGNALHANDLER_HPP
#define WAVEFORMSIGNALHANDLER_HPP

#include <QObject>
#include "wave_form.h"
#include <memory>

class WaveFormSignalHandler : public QObject {
    Q_OBJECT

    public:
        WaveFormSignalHandler(std::shared_ptr<WaveForm> waveForm);
        ~WaveFormSignalHandler();

    public slots:
        void waveformChanged(int);
        void frequencyChanged(double);
        // TODO: Implement this...a
        void phaseChanged(double);

    private:
        std::shared_ptr<WaveForm> m_waveForm;
};

#endif