#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../World.hpp"
#include "../../zf/zf_rect.hpp"
#include "../../zf/zf_sprite.hpp"
#include <iostream>
GameScreen::GameScreen(DisplayManager& manager)
    : DisplayObject(manager), currentWorld(0)
{
}

GameScreen::~GameScreen()
{
}

bool GameScreen::init(DisplayData* data)
{
    auto worldSize = manager.game.WorldSize;
    const int Xs[2] = { 0, worldSize.x + 1 };
    const int Ys[2] = { 1, worldSize.y + 2 };
    infoRegions.push_back(sf::IntRect(Xs[0], Ys[0], worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[0], Ys[0] + 1, worldSize.x, worldSize.y));
    infoRegions.push_back(sf::IntRect(Xs[1], Ys[0], worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[1], Ys[0] + 1, worldSize.x, worldSize.y));
    infoRegions.push_back(sf::IntRect(Xs[1], Ys[1], worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[1], Ys[1] + 1, worldSize.x, worldSize.y));
    infoRegions.push_back(sf::IntRect(Xs[0], Ys[1], worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[0], Ys[1] + 1, worldSize.x, worldSize.y));
    int worldId = 0;
    for (auto region : worldRegions)
    {
        auto window = manager.terminal.newWindow(region);
        World* world = new World(manager.game, worldId++);
        worldWindows.push_back(window);
        worlds.push_back(world);
    } 
    
    for (auto region : infoRegions)
    {
        auto window = manager.terminal.newWindow(region);
        infoWindows.push_back(window);
    }
    auto termSize = manager.game.TermSize;
    overlayWindow = manager.terminal.newWindow(sf::IntRect(0, 0, termSize.x, termSize.y));
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
    for (auto world : worlds)
    {
        world->update(delta);
    }
    /**
     * damn hackish, I should have another container to do it.
     */
    {
        auto blocks = worlds[0]->getOutputBlocks();
        for (auto block : blocks)
        {
            worlds[1]->spawnObject(block);
        }
        blocks = worlds[1]->getOutputBlocks();
        for (auto block : blocks)
        {
            worlds[2]->spawnObject(block);
        }
        blocks = worlds[2]->getOutputBlocks();
        for (auto block : blocks)
        {
            worlds[3]->spawnObject(block);
        }
        blocks = worlds[3]->getOutputBlocks();
        for (auto block : blocks)
        {
            worlds[0]->spawnObject(block);
        }
    }
}

void GameScreen::draw(const sf::Time& delta)
{
    for (int i = 0; i < worlds.size(); i++)
    {
        worlds[i]->draw(worldWindows[i], infoWindows[i], overlayWindow, delta);
    }
    {
        auto w1Region = worldRegions[0];
        int x = zf::rightOf(w1Region) + 1;
        for (int y = w1Region.top; y < w1Region.top + w1Region.height; y++)
        {
            overlayWindow->putChar_xy(x, y, '>', sf::Color(100, 100, 100, 255));
        }
    }
    {
        auto w2Region = worldRegions[1];
        int y = zf::bottomOf(w2Region) + 1;
        for (int x = w2Region.left; x < w2Region.left + w2Region.width; x++)
        {
            overlayWindow->putChar_xy(x, y, 'v', sf::Color(100, 100, 100, 255));
        }
    }
    {
        auto w3Region = worldRegions[2];
        int x = zf::leftOf(w3Region) - 1;
        for (int y = w3Region.top; y < w3Region.top + w3Region.height; y++)
        {
            overlayWindow->putChar_xy(x, y, '<', sf::Color(100, 100, 100, 255));
        }
    }
    {
        auto w4Region = worldRegions[3];
        int y = zf::topOf(w4Region) - 1;
        for (int x = w4Region.left; x < w4Region.left + w4Region.width; x++)
        {
            overlayWindow->putChar_xy(x, y, '^', sf::Color(100, 100, 100, 255));
        }
    }
}

void GameScreen::selectWorld(int world)
{
    if (world < 0 || world >= 4)
    {
        return;
    }
    worlds[currentWorld]->setSelected(false);
    currentWorld = world;
    worlds[currentWorld]->setSelected(true);
}
