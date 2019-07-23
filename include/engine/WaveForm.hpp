#ifndef WAVEFORM_HPP
#define WAVEFORM_HPP

#include <vector>
#include "math.h"

namespace engine {
    enum WaveTypes {
        SINE = 0,
        TRIANGLE,
        SAWTOOTH,
        SQUARE,
        NOT_SET
    };

    class WaveForm {
    public:
        WaveForm();
        ~WaveForm();
        
        WaveTypes getWaveType() const;
        void setWaveType(WaveTypes w_type);

        virtual void NotePressed(float freq, bool legato) = 0;
        virtual void NoteReleased(bool legato);

        virtual double getOutput();

        virtual void setFrequency(float freq);
    
    protected:
        float m_freq;
    
    private:
        double phase;
        float increment;


        WaveTypes wType = WaveTypes::NOT_SET;

        static bool tablesInitialized;

        static std::vector<double> sineWaveTable;
        static std::vector<double> triWaveTable;
        static std::vector<double> sawWaveTable;
        static std::vector<double> sqrWaveTable;

        static void generateWaveTables();
        static void generateSineWaveTable();
        static void generateTriWaveTable();
        static void generateSawWaveTable();
        static void generateSquareWaveTable();
    };
}

#endif