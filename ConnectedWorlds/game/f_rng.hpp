/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2013- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 */
#ifndef _GAME_F_RNG_HPP_
#define _GAME_F_RNG_HPP_
#include <random>
#include <vector>
#include <SFML/System.hpp>
#include <chrono>
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
