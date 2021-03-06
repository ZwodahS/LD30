/*
 *           DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 *
 * Copyright (C) 2014- ZwodahS(ericnjf@gmail.com)
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
 *
 * visit http://github.com/ZwodahS/zframework for the latest version
 */
#include "zf_direction.hpp"
#include <random>
namespace zf
{
    Direction oppositeOf(Direction direction)
    {
        switch(direction)
        {
            case Direction::None  : return Direction::None;
            case Direction::North : return Direction::South;
            case Direction::South : return Direction::North;
            case Direction::East  : return Direction::West;
            case Direction::West  : return Direction::East;
            case Direction::NorthEast : return Direction::SouthWest;
            case Direction::NorthWest : return Direction::SouthEast;
            case Direction::SouthEast : return Direction::NorthWest;
            case Direction::SouthWest : return Direction::NorthEast;
        }
    }

    sf::Vector2i getModifier(Direction direction)
    {
        sf::Vector2i xy;
        switch(direction)
        {
            case Direction::None      : xy.y = 0  ; xy.x = 0  ; break ;
            case Direction::North     : xy.y = -1 ; xy.x = 0  ; break ; 
            case Direction::East      : xy.y = 0  ; xy.x = 1  ; break ; 
            case Direction::South     : xy.y = 1  ; xy.x = 0  ; break ; 
            case Direction::West      : xy.y = 0  ; xy.x = -1 ; break ; 
            case Direction::NorthEast : xy.y = -1 ; xy.x = 1  ; break ; 
            case Direction::SouthEast : xy.y = 1  ; xy.x = 1  ; break ; 
            case Direction::SouthWest : xy.y = 1  ; xy.x = -1 ; break ; 
            case Direction::NorthWest : xy.y = -1 ; xy.x = -1 ; break ; 
            // default : none 
        }
        return xy;
    }

    bool isOpposite(Direction direction1, Direction direction2)
    {
        return oppositeOf(direction1) == direction2;
    }

    int getIntValue(Direction direction)
    {
        switch(direction)
        {
            case Direction::None  : return 0;
            case Direction::North : return 1;
            case Direction::South : return 2;
            case Direction::East  : return 3;
            case Direction::West  : return 4;
            case Direction::NorthEast : return 5;
            case Direction::NorthWest : return 6;
            case Direction::SouthEast : return 7;
            case Direction::SouthWest : return 8;
        }
    }

    std::string directionToString(Direction direction)
    {
        return DirectionString[getIntValue(direction)];
    }

    bool stringToDirection(const std::string& str, Direction& direction)
    {
        for (int i = 0; i < 9; i++)
        {
            if (str == DirectionString[i])
            {
                direction = AllDirection[i];
                return true;
            }
        }
        return false;
    }

    int toBit(Direction direction)
    {
        switch(direction)
        {
            case Direction::None  : return 0;
            case Direction::North : return 1;
            case Direction::East  : return 2;
            case Direction::South : return 4;
            case Direction::West  : return 8;
            case Direction::NorthEast : return toBit(Direction::North) | toBit(Direction::East);
            case Direction::NorthWest : return toBit(Direction::North) | toBit(Direction::West);
            case Direction::SouthEast : return toBit(Direction::South) | toBit(Direction::East);
            case Direction::SouthWest : return toBit(Direction::South) | toBit(Direction::West);
        }
    }
}
