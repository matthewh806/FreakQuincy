#include "engine/AbstractEnvelope.hpp"

namespace engine {
    void AbstractEnvelope::notePressed(float freq, bool legato) {
        if(legato)
            return;

        m_state = 0.0;

        /*
            TODO: Ramp down does not actually go to zero 
            The value gets closer to zero - and then attack 
            just starts from that value again

            maybe its not noticeable as the value tends to be < 10^-4
            but the higher the value the ramp down begins from
            the further from 0 it will actually be after the 0.03 seconds 
            have elapsed. 
        */
        if(m_curParamVal > 0.0) {
            goToStage(RAMP_DOWN);
        } else {
            goToStage(ATTACK);
        }
    }

    void AbstractEnvelope::noteReleased(bool legato) {
        if(m_stage >= RELEASE || legato)
            return;
        
        goToStage(RELEASE);
        m_state = 0.0;
    }

    void AbstractEnvelope::goToStage(STAGE stage) {
        m_stage = stage;
        m_prevParamVal = m_curParamVal;
    }
}