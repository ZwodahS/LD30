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
