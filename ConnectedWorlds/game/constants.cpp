/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2013- ZwodahS(ericnjf@gmail.com)
 * zwodahs.github.io
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE F*** YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 */
#include "Game.hpp"
#include "worlds/World.hpp"
#include "../ResourcePath.hpp"
// need to enforce order of definition
const std::string Game::Title("Connected Worlds");
const std::string Game::Version("1.2.1");
const std::string Game::VersionName("Post-LD");
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
