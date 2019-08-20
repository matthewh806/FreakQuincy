#ifndef MIXER_HPP
#define MIXER_HPP

#include <map>
#include "engine/ModuleBase.hpp"
#include "engine/VCO.hpp"

namespace engine {

    class Mixer : public ModuleBase {

        public:
            void addVCO(VCO* vco, float weight) {
                auto it = m_vco_weights.find(vco);

                if(it == m_vco_weights.end())
                    m_vco_weights.insert(std::pair<VCO*, float>(vco, weight));
            }

            void removeVCO(VCO* vco) {
                auto it = m_vco_weights.find(vco);
                
                if(it == m_vco_weights.end())
                    return;

                m_vco_weights.erase(vco);
            }

            void changeVCOWeight(VCO* vco, float weight) {
                auto it = m_vco_weights.find(vco);

                if(it == m_vco_weights.end())
                    return;

                m_vco_weights[vco] = weight;
            }

            double tick();

        private:
            std::map<VCO*, float> m_vco_weights;
    };
}

#endif