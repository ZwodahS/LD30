#ifndef _GAME_OBJECTS_ENVIRONMENTOBJECT_HPP_
#define _GAME_OBJECTS_ENVIRONMENTOBJECT_HPP_
#include "WorldObject.hpp"
class EnvironmentObject : public WorldObject
{
public:
    enum class EnvObjectType
    {
        BlockType,
    };
    EnvironmentObject(Game& game, World& world, EnvObjectType envType);
    ~EnvironmentObject();
    
    const EnvObjectType envType;
private:
};
#endif
