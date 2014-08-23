#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../World.hpp"
#include "../../zf/zf_rect.hpp"
#include "../../zf/zf_sprite.hpp"
#include <iostream>
GameScreen::GameScreen(DisplayManager& manager)
    : DisplayObject(manager)
{
}

GameScreen::~GameScreen()
{
}

bool GameScreen::init(DisplayData* data)
{
    auto worldSize = manager.game.WorldSize;
    worldRegions.push_back(sf::IntRect(0, 0, worldSize.x, worldSize.y));
    worldRegions.push_back(sf::IntRect(worldSize.x + 1, 0, worldSize.x, worldSize.y));
    worldRegions.push_back(sf::IntRect(worldSize.x + 1, worldSize.y + 1, worldSize.x, worldSize.y));
    worldRegions.push_back(sf::IntRect(0, worldSize.y + 1, worldSize.x, worldSize.y));
    int worldId = 0;
    for (auto region : worldRegions)
    {
        auto window = manager.terminal.newWindow(region);
        World* world = new World(manager.game, worldId++);
        worldWindows.push_back(window);
        worlds.push_back(world);
    } 
    
    worldActions.push_back(Action::Up);
    worldActions.push_back(Action::Down);
    worldActions.push_back(Action::Left);
    worldActions.push_back(Action::Right);
    worldActions.push_back(Action::Select);
    selectWorld(0);
    return true;
}

DisplayData* GameScreen::getReturnValue()
{
    return nullptr;
}

void GameScreen::destroy()
{
}

bool GameScreen::processKey(int key)
{
    auto action = manager.game.keyMap.getMapping(key);
    if (std::find(worldActions.begin(), worldActions.end(), action) != worldActions.end())
    {
        worlds[currentWorld]->processAction(action);
    }
    else
    {
        if (key >= '1' && key <= '4')
        {
            selectWorld(key - '1');
        }
    }
    return true;
}

void GameScreen::childReturned(DisplayObject* child, DisplayData* data)
{
}

void GameScreen::update(const sf::Time& delta)
{
}

void GameScreen::draw(const sf::Time& delta)
{
    for (int i = 0; i < worlds.size(); i++)
    {
        worlds[i]->draw(worldWindows[i], delta);
    }
}

void GameScreen::selectWorld(int world)
{
    if (world < 0 || world >= 4)
    {
        return;
    }
    currentWorld = world;
    worlds[currentWorld]->setSelected(false);
    currentWorld = world;
    worlds[currentWorld]->setSelected(true);
}
