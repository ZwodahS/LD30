#ifndef _GAME_F_LOG_HPP_
#define _GAME_F_LOG_HPP_
#include <string>
namespace logger
{
    void log(const std::string& message);
    void debug(const std::string& message);
    void error(const std::string& message);
}
#endif
