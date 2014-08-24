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
