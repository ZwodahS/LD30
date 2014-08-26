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
#ifndef _GAME_UI_DISPLAYOBJECT_HPP_
#define _GAME_UI_DISPLAYOBJECT_HPP_
#include <SFML/Graphics.hpp>
class DisplayManager;
class DisplayData;
class DisplayObject
{
public:
    DisplayObject(DisplayManager& manager);
    virtual ~DisplayObject();

    DisplayManager& manager;
    bool done;
  
    virtual bool init(DisplayData* data) = 0; 
    virtual DisplayData* getReturnValue() = 0;
    virtual void destroy() = 0;
    /**
     * Process this key.
     * If the key is processed or ignored, return true.
     * return false if the key is to be passed to the previous state to handle.
     *
     * I don't really see a situation where input needs to be passed to the parent state,
     * but having this here first will allow that option in the future if we ever need that.
     */
    virtual bool processKey(int key) = 0;
    virtual void childReturned(DisplayObject* object, DisplayData* data) = 0;
    virtual void update(const sf::Time& delta) = 0;
    virtual void draw(const sf::Time& delta) = 0;
};
#endif
