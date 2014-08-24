#include "FirstHelpScreen.hpp"
#include "DisplayManager.hpp"
#include "../c_colors.hpp"
#include "../../zf/zf_rect.hpp"
#include "../Game.hpp"
#include "../KeyMap.hpp"
FirstHelpScreen::FirstHelpScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

FirstHelpScreen::~FirstHelpScreen()
{
}

bool FirstHelpScreen::init(DisplayData* data)
{
    auto display = manager.displayRegion;
    region = sf::IntRect(display.left + 3, display.top + 3, display.width - 6, display.height - 6);
    window = manager.terminal.newWindow(region);
    firstDraw();
    return true;
}

void FirstHelpScreen::firstDraw()
{
    window->clear(sf::Color(20, 20, 20, 255));
    window->drawEdgeBorder(); 
}

void FirstHelpScreen::destroy()
{
    if (window)
    {
        manager.terminal.freeWindow(*window);
    }
}

bool FirstHelpScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (action == Action::Cancel)
    {
        done = true;
    }
    return true;
}

void FirstHelpScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void FirstHelpScreen::update(const sf::Time& delta)
{
}

void FirstHelpScreen::draw(const sf::Time& delta)
{
}

DisplayData* FirstHelpScreen::getReturnValue()
{
    return nullptr;
}

