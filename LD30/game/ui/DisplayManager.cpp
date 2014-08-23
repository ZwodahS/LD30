#include "DisplayManager.hpp"
#include "DisplayObject.hpp"
#include "DisplayData.hpp"
#include "MainScreen.hpp"
#include "GameScreen.hpp"
#include "RootObject.hpp"
DisplayManager::DisplayManager(Game& game, zf::Terminal& term, const sf::IntRect& displayRegion)
    : game(game), terminal(term), displayRegion(displayRegion)
{
}

DisplayManager::~DisplayManager()
{
}


void DisplayManager::processKey(int key)
{
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        if ((**it).processKey(key))
        {
            break;
        }
    }
}

void DisplayManager::updateAll(const sf::Time& delta)
{
    auto display = stack.size() ? stack.back() : nullptr;
    while (display && display->done)
    {
        stack.pop_back();
        auto returnVal = display->getReturnValue();
        if (stack.size())
        {
            stack.back()->childReturned(display, returnVal);
        }
        display->destroy();
        delete display;
        delete returnVal;
        display = stack.size() ? stack.back() : nullptr;
    }
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        if (!(**it).done)
        {
            (**it).update(delta);
        }
    }
}

void DisplayManager::drawAll(const sf::Time& delta)
{
    for (auto it = stack.begin(); it != stack.end(); it++)
    {
        (**it).draw(delta);
    }
}

void DisplayManager::putDisplay(DisplayObject& object)
{
    stack.push_back(&object);
}

bool DisplayManager::empty() const
{
    return stack.size() == 0;
}

DisplayObject* DisplayManager::makeRoot()
{
    DisplayObject* object = new RootObject(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeMainScreen()
{
    DisplayObject* object = new MainScreen(*this);
    object->init(nullptr);
    return object;
}

DisplayObject* DisplayManager::makeGameScreen()
{
    DisplayObject* object = new GameScreen(*this);
    object->init(nullptr);
    return object;
}
