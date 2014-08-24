#ifndef _GAME_UI_SECONDHELPSCREEN_HPP_
#define _GAME_UI_SECONDHELPSCREEN_HPP_
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "../../zf/zf_term.hpp"
class SecondHelpScreen  : public DisplayObject
{
public:
    SecondHelpScreen(DisplayManager& manager);
    ~SecondHelpScreen();

    virtual bool init(DisplayData* data);
    virtual DisplayData* getReturnValue();
    virtual void destroy();
    virtual bool processKey(int key);
    virtual void childReturned(DisplayObject* child, DisplayData* data);
    virtual void update(const sf::Time& delta);
    virtual void draw(const sf::Time& delta);

private:
    sf::IntRect region;
    zf::TermWindow* window;

    void firstDraw();
};
#endif
