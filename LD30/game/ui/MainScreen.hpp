#ifndef _GAME_UI_MAINSCREEN_HPP_
#define _GAME_UI_MAINSCREEN_HPP_
#include "DisplayObject.hpp"
class MainScreen : public DisplayObject
{
public:
    MainScreen(DisplayManager& manager);
    ~MainScreen();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);
};
#endif
