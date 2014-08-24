#include "BalanceConfig.hpp"
#include "../json11/json11.hpp"
#include <fstream>
#include <iostream>
BalanceConfig::BalanceConfig()
    : Player_InitialFood(100), Player_FoodDepleteRate(10)
    , Player_WorkDepleteRate(10), Player_FoodIncreaseAmount(25)
    , Player_MoveCost(1), Player_GrabCost(1), Player_PushCost(1)
    , Water_FloodProbability(10)
    , Volcano_EruptMin(5), Volcano_EruptMax(10), Volcano_EruptFrequency(30)
{
}

void BalanceConfig::load(const std::string& path)
{
    std::ifstream stream;
    stream.open(path);
    if(stream.is_open())
    {
        std::string line;
        std::string data;
        while(getline(stream, line))
        {
            data += line;
        }
        std::string err = "";
        auto dataobj = json11::Json::parse(data, err);
        if (err != "")
        {
            std::cout << err << std::endl;
            return;
        }
        if (!dataobj["initial_food"].is_null()) { Player_InitialFood = dataobj["initial_food"].int_value(); }
        if (!dataobj["player_fooddepleterate"].is_null()) { Player_FoodDepleteRate = dataobj["player_fooddepleterate"].int_value(); }
        if (!dataobj["player_workdepleterate"].is_null()) { Player_WorkDepleteRate = dataobj["player_workdepleterate"].int_value(); }
        if (!dataobj["player_foodincreaseamount"].is_null()) { Player_FoodIncreaseAmount = dataobj["player_foodincreaseamount"].int_value(); }
        if (!dataobj["player_movecost"].is_null()) { Player_MoveCost = dataobj["player_movecost"].int_value(); }
        if (!dataobj["player_grabcost"].is_null()) { Player_GrabCost = dataobj["player_grabcost"].int_value(); }
        if (!dataobj["player_pushcost"].is_null()) { Player_PushCost = dataobj["player_pushcost"].int_value(); }
        if (!dataobj["water_floodprobability"].is_null()) { Water_FloodProbability = dataobj["water_floodprobability"].int_value(); }
        if (!dataobj["volcano_eruptmin"].is_null()) { Volcano_EruptMin = dataobj["volcano_eruptmin"].int_value(); }
        if (!dataobj["volcano_eruptmax"].is_null()) { Volcano_EruptMax = dataobj["volcano_eruptmax"].int_value(); }
        if (!dataobj["volcano_eruptfreq"].is_null()) { Volcano_EruptFrequency = dataobj["volcano_eruptfreq"].int_value(); }
    }
    else
    {
        std::cout << "no balance file found" << std::endl;
    }
}
