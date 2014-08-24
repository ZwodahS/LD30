#ifndef _GAME_OBJECTS_TREEOBJECT_HPP_
#define _GAME_OBJECTS_TREEOBJECT_HPP_
#include "WorldObject.hpp"
class TreeObject : public WorldObject
{
public:
    static const int STAGES = 5;
    TreeObject(Game& game, World& world);
    virtual ~TreeObject();

    virtual void draw(zf::TermWindow* window, const sf::Time& delta);
    bool canBeGrabbed() const;
    bool grow();
    bool hasFood() const;
    int currentStage;
private:
    sf::Sprite background;
    sf::Sprite sprite[STAGES];
};
#endif
