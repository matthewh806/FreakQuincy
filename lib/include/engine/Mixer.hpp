#ifndef MIXER_HPP
#define MIXER_HPP

#include <map>
#include "engine/ModuleBase.hpp"
#include "engine/VCO.hpp"

namespace engine {

    class Mixer : public ModuleBase {

        public:
            Mixer() : ModuleBase("Mixer") {};
            ~Mixer() {};

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

            float getVCOWeight(VCO* vco) {
                auto it = m_vco_weights.find(vco);

                if(it == m_vco_weights.end()) 
                    return 0.0;

                return m_vco_weights[vco];
            }

            void changeVCOWeight(VCO* vco, float weight) {
                auto it = m_vco_weights.find(vco);

                if(it == m_vco_weights.end())
                    return;

                if(weight < 0.0) weight = 0.0;
                if(weight > 1.0) weight = 1.0;

                m_vco_weights[vco] = weight;
            }

            double tick(double input = 0) override;

        private:
            std::map<VCO*, float> m_vco_weights;
    };
}

#endif