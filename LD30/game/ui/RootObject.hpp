#ifndef _GAME_UI_ROOTOBJECT_HPP_
#define _GAME_UI_ROOTOBJECT_HPP_
#include "DisplayObject.hpp"
#include "../../zf/zf_term.hpp"
class RootObject : public DisplayObject
{
public: 
    RootObject(DisplayManager& manager);
    ~RootObject();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);
private:
    zf::TermWindow* fps;
    DisplayObject* currentChild;
};
#endif
