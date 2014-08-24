#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../worlds/World.hpp"
#include "../worlds/VolcanoWorld.hpp"
#include "../worlds/ForestWorld.hpp"
#include "../worlds/SandWorld.hpp"
#include "../worlds/WaterWorld.hpp"
#include "../objects/g_objects.hpp"
#include "../../zf/zf_rect.hpp"
#include "../../zf/zf_sprite.hpp"
#include <iostream>
const std::string GameScreen::OutDataType("GS_OUT");
GameScreen::GameScreen(DisplayManager& manager)
    : DisplayObject(manager), currentWorld(0), child(nullptr), result(nullptr), paused(false)
{
    for (int i = 0; i < 4; i++)
    {
        arrows[i] = manager.game.getSpecialCharSprite(zf::Arrow[i]);
        arrows[i].setColor(sf::Color(100, 100, 100, 255));
    }
}

GameScreen::~GameScreen()
{
}

GameScreen::OutData::OutData(GameScreen::Result result)
    : DisplayData(OutDataType), result(result)
{
}

bool GameScreen::init(DisplayData* data)
{
    auto worldSize = manager.game.WorldSize;
    const int Xs[2] = { 0, worldSize.x + 1 };
    const int Ys[2] = { 0, worldSize.y + 2 };
    infoRegions.push_back(sf::IntRect(Xs[0], Ys[0], worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[0], Ys[0] + 1, worldSize.x, worldSize.y));
    infoRegions.push_back(sf::IntRect(Xs[1], Ys[0], worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[1], Ys[0] + 1, worldSize.x, worldSize.y));

    infoRegions.push_back(sf::IntRect(Xs[1], Ys[1] + worldSize.y, worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[1], Ys[1], worldSize.x, worldSize.y));
    infoRegions.push_back(sf::IntRect(Xs[0], Ys[1] + worldSize.y, worldSize.x, 1));
    worldRegions.push_back(sf::IntRect(Xs[0], Ys[1], worldSize.x, worldSize.y));
    int worldId = 0;
    for (auto region : worldRegions)
    {
        auto window = manager.terminal.newWindow(region);
        worldWindows.push_back(window);
        window = manager.terminal.newWindow(region);
        objectsWindow.push_back(window);
    } 
    
    for (auto region : infoRegions)
    {
        auto window = manager.terminal.newWindow(region);
        infoWindows.push_back(window);
    }
    World* dWorld = new SandWorld(manager.game);
    worlds.push_back(dWorld);
    World* wWorld = new WaterWorld(manager.game);
    worlds.push_back(wWorld);
    World* fWorld = new ForestWorld(manager.game);
    worlds.push_back(fWorld);
    World* vWorld = new VolcanoWorld(manager.game);
    worlds.push_back(vWorld);

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
    return result;
}

void GameScreen::destroy()
{
    for (auto window : infoWindows)
    {
        manager.terminal.freeWindow(*window);
    }
    for (auto window : worldWindows)
    {
        manager.terminal.freeWindow(*window);
    }
    for (auto window : objectsWindow)
    {
        manager.terminal.freeWindow(*window);
    }
    for (auto world : worlds)
    {
        delete world;
    }
    manager.terminal.freeWindow(*overlayWindow);    
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
        else if (action == Action::World_Up)
        {
            int newWorld = currentWorld == 0 ? 0 :
                           currentWorld == 1 ? 1 :
                           currentWorld == 2 ? 1 :
                           currentWorld == 3 ? 0 : 0; 
            selectWorld(newWorld);
        }
        else if (action == Action::World_Down)
        {
            int newWorld = currentWorld == 0 ? 3 :
                           currentWorld == 1 ? 2 :
                           currentWorld == 2 ? 2 :
                           currentWorld == 3 ? 3 : 3; 
            selectWorld(newWorld);
        }
        else if (action == Action::World_Left)
        {
            int newWorld = currentWorld == 0 ? 0 :
                           currentWorld == 1 ? 0 :
                           currentWorld == 2 ? 3 :
                           currentWorld == 3 ? 3 : 3; 
            selectWorld(newWorld);
        }
        else if (action == Action::World_Right)
        {
            int newWorld = currentWorld == 0 ? 1 :
                           currentWorld == 1 ? 1 :
                           currentWorld == 2 ? 2 :
                           currentWorld == 3 ? 2 : 2; 
            selectWorld(newWorld);
        }
    }
    return true;
}

void GameScreen::childReturned(DisplayObject* child, DisplayData* data)
{
    if (result)
    {
        done = true;
    }
}

void GameScreen::update(const sf::Time& delta)
{
    if (!child && !paused)
    {
        for (auto world : worlds)
        {
            world->update(delta);
        }
        /**
         * damn hackish, I should have another container to do it.
         */
        {
            int foodCount(0);
            auto blocks = worlds[0]->getOutputBlocks();
            for (auto block : blocks)
            {
                if (!worlds[1]->spawnObject(block))
                {
                    delete block;
                }
            }
            blocks = worlds[1]->getOutputBlocks();
            for (auto block : blocks)
            {
                if (!worlds[2]->spawnObject(block))
                {
                    delete block;
                }
            }
            blocks = worlds[2]->getOutputBlocks();
            for (auto block : blocks)
            {
                if (block->type == WorldObject::ObjectType::TreeObject)
                {
                    foodCount+=1;
                    delete block;
                }
                else if (block->type == WorldObject::ObjectType::AshObject)
                {
                    delete block;
                    worlds[3]->spawnObject(new StoneObject(manager.game, *worlds[3]));
                }
                else
                {
                    if (!worlds[3]->spawnObject(block))
                    {
                        delete block;
                    }
                }
            }
            blocks = worlds[3]->getOutputBlocks();
            for (auto block : blocks)
            {
                worlds[0]->spawnObject(block);
            }

            for (int i = 0; i < foodCount; i++)
            {
                for (int w = 0; w < worlds.size(); w++)
                {
                    auto food = new FoodObject(manager.game, *worlds[w]);
                    if (!worlds[w]->spawnObject(food))
                    {
                        delete food;
                    }
                }
            }
        }
        if (worlds[0]->isAlive & worlds[1]->isAlive & worlds[2]->isAlive & worlds[3]->isAlive)
        {
            auto vWorld = static_cast<VolcanoWorld*>(worlds[3]);
            if (vWorld->volcano->blocked)
            {
                child = manager.makeMessagePopup("Victory ");
                manager.putDisplay(*child);
                if (result)
                {
                    delete result;
                }
                result = new OutData(Result::Victory);
            }
        }
        else
        {
            child = manager.makeMessagePopup("Game over ");
            manager.putDisplay(*child);
            if (result)
            {
                delete result;
            }
            result = new OutData(Result::Defeat);
        }
    }
}

void GameScreen::draw(const sf::Time& delta)
{
    for (int i = 0; i < worlds.size(); i++)
    {
        worlds[i]->draw(worldWindows[i], objectsWindow[i], infoWindows[i], overlayWindow, delta);
    }
    {
        auto w1Region = worldRegions[0];
        int x = zf::rightOf(w1Region) + 1;
        for (int y = w1Region.top; y < w1Region.top + w1Region.height; y++)
        {
            overlayWindow->putSprite_xyf(x, y, arrows[zf::Right]);
        }
    }
    {
        auto w2Region = worldRegions[1];
        int y = zf::bottomOf(w2Region) + 1;
        for (int x = w2Region.left; x < w2Region.left + w2Region.width; x++)
        {
            overlayWindow->putSprite_xyf(x, y, arrows[zf::Down]);
        }
    }
    {
        auto w3Region = worldRegions[2];
        int x = zf::leftOf(w3Region) - 1;
        for (int y = w3Region.top; y < w3Region.top + w3Region.height; y++)
        {
            overlayWindow->putSprite_xyf(x, y, arrows[zf::Left]);
        }
    }
    {
        auto w4Region = worldRegions[3];
        int y = zf::topOf(w4Region) - 1;
        for (int x = w4Region.left; x < w4Region.left + w4Region.width; x++)
        {
            overlayWindow->putSprite_xyf(x, y, arrows[zf::Up]);
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
