#include "c_colors.hpp"
namespace colors
{
    const sf::Color General_ClearColor = sf::Color(20, 20, 20, 255);
    const sf::Color Screen_Default = sf::Color(200, 200, 200, 255);

    const sf::Color Button_Border[4] =
    {
        Screen_Default,                // Mod_Base
        sf::Color(255, 255, 100, 255), // Mod_Base | Mod_Selected
        sf::Color(150, 150, 150, 255), // Mod_Base | Mod_Disabled
        sf::Color(100, 100, 100, 255), // Mod_Base | Mod_Disabled | Mod_Selected
    };
    const sf::Color Button_Text[4] =
    {
        Screen_Default,                // Mod_Base
        sf::Color(255, 255, 100, 255), // Mod_Base | Mod_Selected
        sf::Color(150, 150, 150, 255), // Mod_Base | Mod_Disabled
        sf::Color(100, 100, 100, 255), // Mod_Base | Mod_Disabled | Mod_Selected
    };
}
