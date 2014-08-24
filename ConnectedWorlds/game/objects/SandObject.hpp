#ifndef _GAME_OBJECTS_SANDOBJECT_HPP_
#define _GAME_OBJECTS_SANDOBJECT_HPP_
#include "WorldObject.hpp"
class SandObject : public WorldObject
{
public:
    SandObject(Game& game, World& world);
    virtual ~SandObject();
};
#endif
