#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <memory>

#include "spdlog/sinks/stdout_color_sinks.h"

namespace utilities {
    
    static std::shared_ptr<spdlog::logger> setupLogger(std::string name) {
        auto logger = spdlog::get(name);

        if(not logger)
            logger = spdlog::stdout_color_mt(name);

        return logger;
    }
}

#endif