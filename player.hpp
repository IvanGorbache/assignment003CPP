#include <string>
#include <vector>

#include "intersection.hpp"
#include "constants.hpp"
#include "developmentCard.hpp"

class Player
{
private:
    int victoryPoints;
    std::string name;
    std::vector<Intersection> settlements;
    std::vector<DevelopmentCard> deck;
    int resources[Constants::resoucesNum];
public:
    Player(/* args */);
    ~Player();

    int getVictoryPoints();
    std::vector<Intersection> getSettlements();

    void modifyResouces(Constants::resource type, int count);
};