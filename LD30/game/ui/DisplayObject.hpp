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
  
    /**
     * Init this display with this data.
     * The data will be freed by the manager after it is consumed.
     */
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
