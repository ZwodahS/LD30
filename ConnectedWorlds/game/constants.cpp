#include "Game.hpp"
#include "worlds/World.hpp"
#include "../ResourcePath.hpp"
// need to enforce order of definition
const std::string Game::Title("Connected Worlds");
const sf::Vector2i Game::WorldSize(15, 15);
const sf::Vector2i Game::TermSize(2 * WorldSize.x + 1, 2 * WorldSize.y + 4);
const sf::Vector2i Game::ImageSize(32, 32);
const int Game::NO_KEY(-1);
const int Game::ENTER_KEY(10);
const int Game::ESCAPE_KEY = 27;
const int Game::UP_KEY = 128 + 1;
const int Game::DOWN_KEY = 128 + 2;
const int Game::LEFT_KEY = 128 + 4;
const int Game::RIGHT_KEY = 128 + 8;
const int Game::Framerate = 30;
#ifdef APPBUNDLE
const std::string Game::RootPath = resourcePath() + "/";
#else
const std::string Game::RootPath = "";
#endif
