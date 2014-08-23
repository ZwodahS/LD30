#ifndef _GAME_OBJECTS_BLOCKOBJECT_HPP_
#define _GAME_OBJECTS_BLOCKOBJECT_HPP_
#include "WorldObject.hpp"
#include "../../zf/zf_term.hpp"
#include "../../zf/zf_direction.hpp"
/**
 * There are 2 type of block type, one that is straight,
 * and the other that is L shape
 *
 * There are 4 color, each naturally spawn in their own world.
 */
class BlockObject : public WorldObject
{
public:
    static const sf::Color colors[4];
    BlockObject(Game& game, World& world, int colorType, zf::Direction orientation, int level = 1);
    virtual ~BlockObject();

    const int colorType; // follow the world's id
    const int level;
    std::vector<zf::Direction> getOutputDirections() const;
    static std::vector<zf::Direction> getOutputDirections(zf::Direction orientation);

    void draw(zf::TermWindow* window, const sf::Time& delta);
    

    std::vector<BlockObject*> getConnectedBlocks() const;
    
    bool canConnectFrom(zf::Direction direction) const;
private:
    sf::Sprite background;
    sf::Sprite sprite;
    /**
     * There are 2 orientation.
     * For straight, it can be one of the single direction orientation
     * For angled, it can be one of the 2 direction orientation
     */
    zf::Direction orientation;

};
#endif
