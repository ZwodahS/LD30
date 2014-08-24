#include "SecondHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
SecondHelpScreen::SecondHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

SecondHelpScreen::~SecondHelpScreen()
{
}

bool SecondHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void SecondHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
}

void SecondHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool SecondHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void SecondHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void SecondHelpScreen::update(const sf::Time& delta)
{
}

void SecondHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* SecondHelpScreen::getReturnValue()
{
    return nullptr;
}


