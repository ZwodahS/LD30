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
#ifndef _GAME_OBJECTS_WORLDOBJECT_HPP_
#define _GAME_OBJECTS_WORLDOBJECT_HPP_
#include <SFML/Graphics.hpp>
#include "../../zf/zf_term.hpp"
#include "../../zf/zf_direction.hpp"
class Game;
class World;
class WorldObject 
{
public:
    enum class ObjectType
    {
        PlayerObject,
        AshObject,
        FoodObject,
        WaterObject,
        SandObject,
        VolcanoObject,
        TreeObject,
        StoneObject,
    };
    WorldObject(Game& game, World& world, ObjectType type);
    virtual ~WorldObject();

    void reset();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta) = 0;
    virtual void update(const sf::Time& delta);
    virtual bool isPushable() const;
    virtual bool canGrabbed(zf::Direction direction, WorldObject& grabber, std::vector<WorldObject*> otherGrabbedObjects) const;
    virtual bool canBeGrabbed() const;
    virtual bool grab();
    virtual void drop();

    virtual void objectMoved();

    const ObjectType type;
    World* world;
    sf::Vector2i position;
    Game& game;

    bool grabbed;

    bool markedForRemoval;
    /**
     * Used together with markedForRemoval,
     * this prevent it from being deleted. Instead it is returned to the gamescreen.
     */
    bool isSpawnElsewhere;
};
#endif
