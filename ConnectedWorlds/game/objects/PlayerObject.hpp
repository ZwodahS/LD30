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
#ifndef _GAME_OBJECTS_PLAYEROBJECT_HPP_
#define _GAME_OBJECTS_PLAYEROBJECT_HPP_
#include "WorldObject.hpp"
class PlayerObject : public WorldObject
{
public:
    static int FoodIncreaseAmount;
    PlayerObject(Game& game, World& world);
    virtual ~PlayerObject();

    void draw(zf::TermWindow* window, const sf::Time& delta);
    void update(const sf::Time& delta);
    bool canPush(zf::Direction direction) const;

    bool isGrabbing() const;
    /**
     * If the player is already holding things, they will be dropped.
     * If no, then it willl grab surrounding things.
     */
    void toggleGrab();
    int food;
    int work;
    bool canMove() const;
    void doWork(int amount);
    virtual void objectMoved();
    void eat();
    const std::vector<WorldObject*>& getGrabbedObjects() const;
private:
    float moveDelay;
    float foodDepleteCounter;
    sf::Sprite sprite;
    std::vector<WorldObject*> grabbedObjects;
};
#endif
