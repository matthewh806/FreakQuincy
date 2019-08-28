#include "engine/LinearTimeADSR.hpp"

namespace engine {

    // void LinearTimeADSR::notePressed(float freq, bool legato) {
    //     if(legato)
    //         return;

    //     m_state = 0.0;

    //     /*
    //         TODO: Ramp down does not actually go to zero 
    //         The value gets closer to zero - and then attack 
    //         just starts from that value again

    //         maybe its not noticeable as the value tends to be < 10^-4
    //         but the higher the value the ramp down begins from
    //         the further from 0 it will actually be after the 0.03 seconds 
    //         have elapsed. 
    //     */
    //     if(m_curParamVal > 0.0) {
    //         m_stage = RAMP_DOWN;
    //         m_prevParamVal = m_curParamVal;
    //     } else {
    //         m_stage = ATTACK;
    //         m_prevParamVal = 0.0;
    //     }
    // }

    void LinearTimeADSR::noteReleased(bool legato) {
        if(m_stage >= RELEASE || legato)
            return;
        
        m_stage = RELEASE;
        m_state = 0.0;
        m_prevParamVal = m_curParamVal;
    }

    double LinearTimeADSR::tick() {
        m_state += m_rate;

        if(m_state >= m_stageTimes[m_stage]) {
            m_state -= m_stageTimes[m_stage];
            m_prevParamVal = m_curParamVal;

            m_stage = static_cast<STAGE>((m_stage + 1) % NUM_STAGES);
        }

        double gamma = m_state / m_stageTimes[m_stage];
        m_curParamVal = (1-gamma) * m_prevParamVal + gamma * m_paramValues[m_stage];
        
        m_lastOut = m_curParamVal * m_depth;

        return m_lastOut;
    }
}