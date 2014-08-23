#include "f_log.hpp"
#include <iostream>
namespace logger
{
    void log(const std::string& message)
    {
        std::cout << "[Log ]" << message << std::endl;
    }

    void debug(const std::string& message)
    {
        std::cout << "[Debug ]" << message << std::endl;
    }

    void error(const std::string& message)
    {
        std::cout << "[Error ]" << message << std::endl;
    }
}
