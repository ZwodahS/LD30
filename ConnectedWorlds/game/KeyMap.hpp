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
#ifndef _GAME_KEYMAP_HPP_
#define _GAME_KEYMAP_HPP_
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>
enum class Action
{
    None,
    Up,
    Left,
    Right,
    Down,

    World_Up,
    World_Down,
    World_Left,
    World_Right,
    Select,
    Cancel,

    World_1,
    World_2,
    World_3,
    World_4,
};

namespace actions
{
    static const Action NavigationAction[4] = { Action::Up, Action::Down, Action::Left, Action::Right };
}

class KeyMap
{
public:
    KeyMap();
    ~KeyMap();

    /**
     * If category is "" 
     * rather this is a "set"
     */
    void addMapping(int c, Action key);

    Action getMapping(int c) const;
    int getKey(Action action) const;

private:
    std::vector<std::pair<int, Action> > keyActionPair;
};
#endif
