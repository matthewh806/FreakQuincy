#include "engine/Filter.hpp"

namespace engine {

    double Filter::tick(double input) {
        
        m_x[0] = input;

        double sum = 0.0;
        for(int n = 1; n <= m_yDelays; n++)
            sum -= m_a[n] * m_y[n];

        for(int m=0; m <= m_xDelays; m++)
            sum += m_b[m] * m_x[m];

        for(int n=m_yDelays; n >= 2; n--)
            m_y[n] = m_y[n-1];
        if(m_yDelays > 0)
            m_y[1] = sum;

        for(int m=m_xDelays; m >= 2; m--)
            m_x[m] = m_x[m-1];
        m_x[1] = m_x[0];

        return sum;
    }
}