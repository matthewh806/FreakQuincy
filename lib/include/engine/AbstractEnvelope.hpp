#ifndef ABSTRACTADSR_HPP
#define ABSTRACTADSR_HPP

#include <iostream>

#include "spdlog/sinks/stdout_color_sinks.h"

#include "engine/Modulator.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    class AbstractEnvelope : public Modulator {
        public:
            AbstractEnvelope(float attackTime, float decayTime, float sustainLevel, float releaseTime, double depth, bool bypass) : Modulator(depth, bypass) {
                m_stageTimes = std::vector<float> { 
                    0.03,
                    attackTime, 
                    decayTime, 
                    std::numeric_limits<float>::infinity(),
                    releaseTime,
                    std::numeric_limits<float>::infinity()
                };

                m_paramValues = std::vector<float> {
                    0,
                    1,
                    sustainLevel,
                    sustainLevel,
                    0,
                    0
                };

                m_rate = 1.0 / AudioSettings::getSampleRate();
                m_state = 0.0;
                m_curParamVal = 0.0;
                m_prevParamVal = 0.0;

                logger = spdlog::stdout_color_mt("Envelope");
            };

            ~AbstractEnvelope() {}

            double getRate() { return m_rate; }

            float getAttackTime() { return m_stageTimes[ATTACK]; }
            void setAttackTime(float t) { m_stageTimes[ATTACK] = t; }

            float getDecayTime() { return m_stageTimes[DECAY]; }
            void setDecayTime(float t) { m_stageTimes[DECAY] = t; }

            float getSustainLevel() { return m_paramValues[SUSTAIN]; }
            void setSustainLevel(float l) {
                m_paramValues[DECAY] = l;
                m_paramValues[SUSTAIN] = l;
            }

            float getReleaseTime() { return m_stageTimes[RELEASE]; }
            void setReleaseTime(float t) { m_stageTimes[RELEASE] = t; }
            
            void notePressed(float freq, bool legato) override;
            void noteReleased(bool legato) override;

            friend std::ostream& operator<<(std::ostream& out, const AbstractEnvelope& adsr) {
                out << "ADSR: (Rate, Attack, Decay, Release): " << adsr.m_rate << ", " << adsr.m_stageTimes[1] << ", " << adsr.m_stageTimes[2] << ", " << adsr.m_stageTimes[4];
                return out;
            }

        protected:
            enum STAGE {
                RAMP_DOWN,
                ATTACK,
                DECAY,
                SUSTAIN,
                RELEASE,
                DONE,
                NUM_STAGES
            };

            STAGE m_stage = DONE;
            double m_state;
            double m_rate; // env time units per tick
            double m_curParamVal; // current parameter value
            double m_prevParamVal; // Parameter value at start of current stage

            // The following vectors follow this pattern: RAMP, A, De, S, R, Do (De = Decay, Do = Done)
            std::vector<float> m_stageTimes;  // Time when each stage ends S,D = inf
            std::vector<float> m_paramValues; // Target param. value of stage De = S, RAMP=R=Do= 0

            std::shared_ptr<spdlog::logger> logger;

            virtual void goToStage(STAGE stage);
    };
}

#endif