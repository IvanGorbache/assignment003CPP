#include <string>
#include <vector>

#include "constants.hpp"

class Player
{
private:
    int victoryPoints;
    std::string name;
    std::vector<Point> Settlements();
    int resources[Constants::pleanty+1];
public:
    Player(/* args */);
    ~Player();

    int getVictoryPoints() const;
    std::vector<Point> getSettlements() const;

    void modifyResouces(Constants::type type, int count);
};