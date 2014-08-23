#include "f_rng.hpp"

namespace rng
{
    std::mt19937 rand = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
    
    int randomInt(int min, int max)
    {
        std::uniform_int_distribution<> dis(min, max);
        return dis(rand);
    }
    
    sf::Vector2i randomVector2i(int xMax, int yMax)
    {
        return sf::Vector2i(randomInt(0, xMax - 1), randomInt(0, yMax - 1));
    }
}
