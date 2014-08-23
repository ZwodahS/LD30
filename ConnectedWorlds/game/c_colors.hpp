#ifndef _GAME_C_COLORS_HPP_
#define _GAME_C_COLORS_HPP_
#include <SFML/Graphics.hpp>
namespace colors
{
    extern const sf::Color General_ClearColor;
    extern const sf::Color Screen_Default;

    const int Mod_Base = 0;
    const int Mod_Selected = 1;
    const int Mod_Disabled = 2;
    extern const sf::Color Button_Border[4];
    extern const sf::Color Button_Text[4];
}
#endif
