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
#ifndef _GAME_BALANCECONFIG_HPP_
#define _GAME_BALANCECONFIG_HPP_
#include <string>
/**
 * Suppose to be constant value, so I shall name it as though it is constants
 */
struct BalanceConfig
{
    int Player_InitialFood;
    int Player_FoodDepleteRate;
    int Player_WorkDepleteRate;
    int Player_FoodIncreaseAmount;

    int Player_MoveCost;
    int Player_GrabCost;
    int Player_PushCost;

    int Water_FloodProbability;

    int Volcano_EruptMin;
    int Volcano_EruptMax;
    int Volcano_EruptFrequency;
    BalanceConfig();

    void load(const std::string& path);
};
#endif
