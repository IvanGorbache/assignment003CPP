#pragma once
#include <string>
namespace Constants
{
    enum type{empty,settlement,city,sea,desert,wood,iron,brick,wheat,wool,knight,monopoly,builder,pleanty,victoryCard,temp};
    extern std::string gameResource[];
    extern const char* gameResourceIcons[];
    const int inventorySize = victoryCard-wood+1;
};