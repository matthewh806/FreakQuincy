#ifndef MODULEBASE_HPP
#define MODULEBASE_HPP

#include <vector>
#include <memory>
#include <utilities/logging.hpp>

namespace engine {
    
    /*
    * TODO: If I start to use copy constructors, assignment operators etc
    * this handling of IDs can become problematic.
    * 
    * Also if I save state to disk for e.g. to reload a patch.
    * 
    * WATCH OUT BOY!
    */
    class ModuleBase {

        public:
            ModuleBase(std::string loggerName) {
                m_id=++counter;
                logger = utilities::setupLogger(loggerName);
            }

            ~ModuleBase() {};

            virtual void notePressed(float freq, bool legato) {};
            virtual void noteReleased(bool legato) {};
            virtual double tick(double input = 0) = 0;

            int getId() const { return m_id; }

        protected:
            int m_id;
            std::shared_ptr<spdlog::logger> logger;

        private:
            static int counter;
    };
}

#endif