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
#include "c_colors.hpp"
namespace colors
{
    const sf::Color General_ClearColor = sf::Color(20, 20, 20, 255);
    const sf::Color Screen_Default = sf::Color(200, 200, 200, 255);

    const sf::Color Button_Border[4] =
    {
        Screen_Default,                // Mod_Base
        sf::Color(255, 255, 100, 255), // Mod_Base | Mod_Selected
        sf::Color(150, 150, 150, 255), // Mod_Base | Mod_Disabled
        sf::Color(100, 100, 100, 255), // Mod_Base | Mod_Disabled | Mod_Selected
    };
    const sf::Color Button_Text[4] =
    {
        Screen_Default,                // Mod_Base
        sf::Color(255, 255, 100, 255), // Mod_Base | Mod_Selected
        sf::Color(150, 150, 150, 255), // Mod_Base | Mod_Disabled
        sf::Color(100, 100, 100, 255), // Mod_Base | Mod_Disabled | Mod_Selected
    };
}
