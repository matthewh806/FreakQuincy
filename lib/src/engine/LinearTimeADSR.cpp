#include "engine/LinearTimeADSR.hpp"

namespace engine {

    double LinearTimeADSR::tick(double input) {
        m_state += m_rate;

        if(m_state >= m_stageTimes[m_stage]) {
            m_state -= m_stageTimes[m_stage];
            goToStage(static_cast<STAGE>((m_stage + 1) % NUM_STAGES));
        }

        double gamma = m_state / m_stageTimes[m_stage];
        m_curParamVal = (1-gamma) * m_prevParamVal + gamma * m_paramValues[m_stage];
        
        m_lastOut = m_curParamVal * m_depth;

        return m_lastOut;
    }
}