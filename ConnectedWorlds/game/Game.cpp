#include "Game.hpp"
#include "c_colors.hpp"
#include "../zf/zf_sprite.hpp"
#include "../ResourcePath.hpp"
#include <iostream>
Game::Game()
    : renderWindow(nullptr), terminal(nullptr), cellSize(16), displayStack(nullptr)
{
}

Game::~Game()
{
    if (terminal)
    {
        delete terminal;
    }
    if (renderWindow)
    {
        delete renderWindow;
    }
    if (displayStack)
    {
        delete displayStack;
    }
}

void Game::init()
{
    initUI();
    initKeys();
    initAssets();
}

void Game::initUI()
{
    screenSize = sf::Vector2i(TermSize.x * cellSize, TermSize.y * cellSize);
    renderWindow = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), Title);
    renderWindow->setFramerateLimit(Framerate);

    terminal = new zf::Terminal(*renderWindow, TermSize);

    terminal->init(sf::Vector2i(cellSize, cellSize), ImageSize);
    displayStack = new DisplayManager(*this, *terminal, sf::IntRect(0, 0, TermSize.x, TermSize.y - 1), sf::IntRect(0, TermSize.y - 1, TermSize.x, 1));
}

void Game::initKeys()
{
    keyMap.addMapping('w', Action::Up);
    keyMap.addMapping('a', Action::Left);
    keyMap.addMapping('s', Action::Down);
    keyMap.addMapping('d', Action::Right);

    keyMap.addMapping('k', Action::Up);
    keyMap.addMapping('h', Action::Left);
    keyMap.addMapping('j', Action::Down);
    keyMap.addMapping('l', Action::Right);

    keyMap.addMapping(' ', Action::Select);
    keyMap.addMapping(ENTER_KEY, Action::Select);
    keyMap.addMapping(ESCAPE_KEY, Action::Cancel);

}

void Game::run()
{
    bool quit(false);
    sf::Clock clock;
    
    displayStack->putDisplay(*displayStack->makeRoot());
    while (!quit && renderWindow->isOpen() && !displayStack->empty())
    {
        sf::Time delta = clock.restart();
        sf::Event event;
        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderWindow->close();
                quit = true;
            }
            else if(event.type == sf::Event::TextEntered)
            {
                // strictly only handles ascii character
                if (event.text.unicode >= 32 && event.text.unicode <= 126)
                {
                    keyQueue.push_back(event.text.unicode);
                }
                else if (event.text.unicode == 10)
                {
                    keyQueue.push_back(event.text.unicode);
                }
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                // handles escape key
                if (event.key.code == sf::Keyboard::Escape)
                {
                    keyQueue.push_back(ESCAPE_KEY);
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    keyQueue.push_back(LEFT_KEY);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    keyQueue.push_back(RIGHT_KEY);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    keyQueue.push_back(UP_KEY);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    keyQueue.push_back(DOWN_KEY);
                }
            }
        }
        update(delta);
        draw(delta);
    }
}

void Game::draw(const sf::Time& delta)
{
    renderWindow->clear(colors::General_ClearColor);
    displayStack->drawAll(delta);
    terminal->updateRenderWindow(false);
    renderWindow->display();
}

void Game::update(const sf::Time& delta)
{
    int key = getNextKey();
    if (key != NO_KEY)
    {
        displayStack->processKey(key);
    }
    displayStack->updateAll(delta);
}

int Game::getNextKey()
{
    int outKey = NO_KEY;
    if (keyQueue.size() != 0)
    {
        outKey = keyQueue.front();
        keyQueue.pop_front();
    }
    return outKey;
}

//////////////////// Assets ////////////////////
void Game::initAssets()
{
    terminal->autoLoad(RootPath + "data/font_32");
    int current = zf::TotalSpecialChar;
    Special_Sand1 = current++;
    Special_Sand2 = current++;
    Special_Sand3 = current++;
    Special_Sand4 = current++;
    Special_Unit = current++;
    Special_Volcano = current++;
    sf::Image image;
    image.loadFromFile(RootPath + "data/others/sand_1.png");
    terminal->addSpecialCharImage(Special_Sand1, image);
    image.loadFromFile(RootPath + "data/others/sand_2.png");
    terminal->addSpecialCharImage(Special_Sand2, image);
    image.loadFromFile(RootPath + "data/others/sand_3.png");
    terminal->addSpecialCharImage(Special_Sand3, image);
    image.loadFromFile(RootPath + "data/others/sand_4.png");
    terminal->addSpecialCharImage(Special_Sand4, image);
    image.loadFromFile(RootPath + "data/others/unit.png");
    std::cout << terminal->addSpecialCharImage(Special_Unit, image) << std::endl;
    image.loadFromFile(RootPath + "data/others/volcano.png");
    terminal->addSpecialCharImage(Special_Volcano, image);
}

sf::Sprite Game::getPlayerSprite(int worldId)
{
    sf::Color color = worldId < 0 || worldId >= 4 ? sf::Color(255, 255, 255) :
                worldId == 0 ? sf::Color(255, 100, 100) :
                worldId == 1 ? sf::Color(100, 255, 100) :
                worldId == 2 ? sf::Color(255, 255, 100) :
                sf::Color(100, 100, 255);
    return zf::setCopyColor(terminal->getSpecialChar(Special_Unit).createSprite(), color);
}

sf::Sprite Game::getCharSprite(char c)
{
    return terminal ? terminal->getChar(c).createSprite() : sf::Sprite();
}

sf::Sprite Game::getSpecialCharSprite(int c)
{
    return terminal ? terminal->getSpecialChar(c).createSprite() : sf::Sprite();
}
