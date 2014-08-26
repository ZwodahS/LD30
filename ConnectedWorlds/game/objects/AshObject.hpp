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
#ifndef _GAME_OBJECTS_ASHOBJECT_HPP_
#define _GAME_OBJECTS_ASHOBJECT_HPP_
#include "WorldObject.hpp"
class AshObject : public WorldObject
{
public:
    static const sf::Color color;
    static const sf::Color grabbedColor;
    AshObject(Game& game, World& world, zf::Direction orientation);
    virtual ~AshObject();

    std::vector<zf::Direction> getOutputDirections() const;
    static std::vector<zf::Direction> getOutputDirections(zf::Direction orientation);

    void draw(zf::TermWindow* window, const sf::Time& delta);
    
    std::vector<AshObject*> getConnectedBlocks() const;
    
    bool canConnectFrom(zf::Direction direction) const;
    bool canBeGrabbed() const;
private:
    sf::Sprite normalBackground;
    sf::Sprite grabbedBackground;
    sf::Sprite sprite;
    /**
     * There are 2 orientation.
     * For straight, it can be one of the single direction orientation
     * For angled, it can be one of the 2 direction orientation
     */
    zf::Direction orientation;

};
#endif
