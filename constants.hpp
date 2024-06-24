#pragma once
namespace Constants
{
    enum type{empty,settlement,city,sea,desert,wood,iron,brick,wheat,wool,knight,monopoly,builder,pleanty,victoryCard,temp};
    std::string resource[] = {"empty","settlement","city","sea","desert","wood","iron","brick","wheat","wool","knight","monopoly","builder","pleanty","victoryCard","temp"};
    const int inventorySize = victoryCard-wood+1;
};