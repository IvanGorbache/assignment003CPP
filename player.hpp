#include <string>
#include <vector>

#include "constants.hpp"
#include "card.hpp"

class Player
{
private:
    int victoryPoints;
    std::string name;
    std::vector<Point> settlements;
    int resources[Constants::wool+1];
    std::vector<Card>[5] deck;

public:
    Player(/* args */);
    ~Player();

    int getVictoryPoints() const;
    std::vector<Point> getSettlements() const;
    bool canTrade(int resource, int amount);
    void modifyResources(int myResource, int myAmount);
    void modifyCards(int card, int amount);
    std::vector<Card> getDeck();

};