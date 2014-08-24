#ifndef _GAME_BALANCECONFIG_HPP_
#define _GAME_BALANCECONFIG_HPP_
#include <string>
/**
 * Suppose to be constant value, so I shall name it as though it is constants
 */
struct BalanceConfig
{
    int Player_InitialFood;
    int Player_FoodDepleteRate;
    int Player_WorkDepleteRate;
    int Player_FoodIncreaseAmount;

    int Player_MoveCost;
    int Player_GrabCost;
    int Player_PushCost;

    int Water_FloodProbability;

    int Volcano_EruptMin;
    int Volcano_EruptMax;
    int Volcano_EruptFrequency;
    BalanceConfig();

    void load(const std::string& path);
};
#endif
