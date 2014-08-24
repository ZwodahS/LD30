#include "ThirdHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
ThirdHelpScreen::ThirdHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

ThirdHelpScreen::~ThirdHelpScreen()
{
}

bool ThirdHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void ThirdHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
}

void ThirdHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool ThirdHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void ThirdHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void ThirdHelpScreen::update(const sf::Time& delta)
{
}

void ThirdHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* ThirdHelpScreen::getReturnValue()
{
    return nullptr;
}


