#include "engine/ExponentialTimeADSR.hpp"
#include "math.h"

namespace engine {
    
    double ExponentialTimeADSR::tick() {
        m_state += m_rate;

        if(m_state >= m_stageTimes[m_stage]) {
            m_state -= m_stageTimes[m_stage];
            goToStage(static_cast<STAGE>((m_stage + 1) % NUM_STAGES));
        }

        m_curParamVal *= gamma;
        m_lastOut = m_curParamVal * m_depth;

        return m_lastOut;
    }

    void ExponentialTimeADSR::goToStage(STAGE stage) {
        std::cout << "current value: " << m_curParamVal << std::endl;
        
        AbstractEnvelope::goToStage(stage);
        calculateMultiplier(m_curParamVal, m_paramValues[m_stage], m_stageTimes[m_stage]);
        if(m_curParamVal == 0.0) { m_curParamVal = 0.0001; }

        std::cout << "Stage: " << m_stage << ", multiplyer: " << gamma << std::endl;
    }

    void ExponentialTimeADSR::calculateMultiplier(double startLevel, double endLevel, double length) {
        std::cout << "length: " << length << std::endl;
        if(length == std::numeric_limits<float>::infinity()) {
            gamma = 1.0;
            return;
        }

        // Log(0) undefined
        if(startLevel == 0.0) { startLevel = 0.0001; }
        if(endLevel == 0.0) { endLevel = 0.0001; }

        gamma = 1 + (log(endLevel) - log(startLevel)) / (length * AudioSettings::getSampleRate());
    }
}