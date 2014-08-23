#include "Game.hpp"
#include "c_colors.hpp"
const std::string Game::Title("LD30");
const sf::Vector2i Game::TermSize(80, 60);
const sf::Vector2i Game::ImageSize(32, 32);
const int Game::NO_KEY = -1;
const int Game::ENTER_KEY = 10;
const int Game::ESCAPE_KEY = 27;
const int Game::UP_KEY = 128 + 1;
const int Game::DOWN_KEY = 128 + 2;
const int Game::LEFT_KEY = 128 + 4;
const int Game::RIGHT_KEY = 128 + 8;
const int Game::Framerate = 30;

Game::Game()
    : renderWindow(nullptr), terminal(nullptr), cellSize(8), displayStack(nullptr)
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
}

void Game::initUI()
{
    screenSize = sf::Vector2i(TermSize.x * cellSize, TermSize.y * cellSize);
    renderWindow = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), Title);
    renderWindow->setFramerateLimit(Framerate);

    terminal = new zf::Terminal(*renderWindow, TermSize);

    terminal->init(sf::Vector2i(cellSize, cellSize), ImageSize);
    terminal->autoLoad("data/font_32");
    displayStack = new DisplayManager(*this, *terminal, sf::IntRect(0, 0, TermSize.x, TermSize.y - 1));
}

void Game::initAssets()
{
}

void Game::run()
{
    bool quit(false);
    sf::Clock clock;
    
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
    terminal->updateRenderWindow();
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
