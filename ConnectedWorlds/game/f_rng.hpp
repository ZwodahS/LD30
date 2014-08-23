#ifndef _GAME_F_RNG_HPP_
#define _GAME_F_RNG_HPP_
#include <random>
#include <vector>
#include <SFML/System.hpp>
namespace rng
{
    extern std::mt19937 rand;
    int randomInt(int min, int max);

    template <class T>
    T randomItem(std::vector<T>& items, T defaultValue, bool remove = false)
    {
        if (!items.size())
        {
            return defaultValue;
        }
        int index = randomInt(0, items.size() - 1);
        T v = items[index];
        if (remove)
        {
            items.erase(items.begin() + index);
        }
        return v;
    }

    /** 
     * max exclusive, 
     */
    sf::Vector2i randomVector2i(int xMax, int yMax);
}
#endif
