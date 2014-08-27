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
#include "KeyMap.hpp"
#include <iostream>
KeyMap::KeyMap()
{
}

KeyMap::~KeyMap()
{
}

void KeyMap::addMapping(int c, Action key)
{
    for (auto it = keyActionPair.begin(); it != keyActionPair.end(); )
    {
        if ((*it).first == c || (*it).second == key)
        {
            it = keyActionPair.erase(it);
        }
        else
        {
            it++;
        }
    }
    keyActionPair.push_back(std::pair<int, Action>(c, key));
}

Action KeyMap::getMapping(int c) const
{
    for (auto pair : keyActionPair)
    {
        if (pair.first == c)
        {
            return pair.second;
        }
    }
    return Action::None;
}

int KeyMap::getKey(Action action) const
{
    for (auto pair : keyActionPair)
    {
        if (pair.second == action)
        {
            return pair.first;
        }
    }
    return -1;
}
