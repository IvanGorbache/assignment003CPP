#include "catan.hpp"

Catan::Catan(Player *p1, Player *p2, Player *p3)
{
    this->players[0] = p1;
    this->players[1] = p2;
    this->players[2] = p3;

    std::fill_n(this->firstTurn, 3, false);

    int originalMap[12][11]= 
    {
        {Constants::sea, Constants::sea, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::sea, Constants::sea},
        {Constants::sea, Constants::sea, Constants::empty, Constants::iron, Constants::empty, Constants::wool, Constants::empty, Constants::wood, Constants::empty, Constants::sea, Constants::sea},
        {Constants::sea, Constants::sea, Constants::empty, Constants::iron, Constants::empty, Constants::wool, Constants::empty, Constants::wood, Constants::empty, Constants::sea, Constants::sea},
        {Constants::sea, Constants::empty, Constants::wheat, Constants::empty, Constants::brick, Constants::empty, Constants::wool, Constants::empty, Constants::brick, Constants::empty, Constants::sea},
        {Constants::sea, Constants::empty, Constants::wheat, Constants::empty, Constants::brick, Constants::empty, Constants::wool, Constants::empty, Constants::brick, Constants::empty, Constants::sea},
        {Constants::empty, Constants::wheat, Constants::empty, Constants::wood, Constants::empty, Constants::desert, Constants::empty, Constants::wood, Constants::empty, Constants::iron, Constants::empty},
        {Constants::empty, Constants::wheat, Constants::empty, Constants::wood, Constants::empty, Constants::desert, Constants::empty, Constants::wood, Constants::empty, Constants::iron, Constants::empty},
        {Constants::sea, Constants::empty, Constants::wood, Constants::empty, Constants::iron, Constants::empty, Constants::wheat, Constants::empty, Constants::wool, Constants::empty, Constants::sea},
        {Constants::sea, Constants::empty, Constants::wood, Constants::empty, Constants::iron, Constants::empty, Constants::wheat, Constants::empty, Constants::wool, Constants::empty, Constants::sea},
        {Constants::sea, Constants::sea, Constants::empty, Constants::wood, Constants::empty, Constants::wheat, Constants::empty, Constants::wool, Constants::empty, Constants::sea, Constants::sea},
        {Constants::sea, Constants::sea, Constants::empty, Constants::wood, Constants::empty, Constants::wheat, Constants::empty, Constants::wool, Constants::empty, Constants::sea, Constants::sea},
        {Constants::sea, Constants::sea, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::sea, Constants::sea},
    };

    for(int i = 0;i<12;i++)
    {
        for(int j = 0;j<11;j++)
        {
            map[i][j] = Point(0,i,j,originalMap[i][j]);
            if(Constants::wood<=originalMap[i][j]<=Constants::wool)
            {
                map[i][j].setID(rand() % (12 - 2 + 1) + 2);
                if(originalMap[i][j] == originalMap[i][j-1])
                {
                    map[i][j-1] = map[i][j]; 
                }
            }
        }
    }
}

void Catan::rollDice(int cheat = 0)
{
    Point* area[4];
    unsigned int x, y;
    int roll = cheat, amount = 0;
    if (!cheat)
    {
        roll = rand() % (12 - 2 + 1) + 2; 
    }

    for (Player *player : this->players)
    {
        for (Point settlement : player->getSettlements())
        {
            x = settlement.getX();
            y = settlement.getY();
            area[0] = x + 1 < 11 ? &map[x + 1][y] : NULL;
            area[1] = x - 1 >= 0 ? &map[x - 1][y] : NULL;
            area[2] = y + 1 < 12 ? &map[x][y + 1] : NULL;
            area[3] = y - 1 >= 0 ? &map[x][y - 1] : NULL;

            amount = settlement.getClassification() == Constants::settlement ? 1 : 2;

            for (Point* p : area)
            {
                if (p != NULL && p->getId() == roll)
                {
                    player->modifyResources(p->getId(),amount);
                }
            }
        }
    }
}


void Catan::placeSettelemnt(Point a)
{
    bool canPlace = false;
    if(a.getClassification() == Constants::empty)
    {
        if(a.getOwner() == NULL && a.getClassification() == Constants::empty && a.getNeighbors().size()>0)
        {
            for(Point neighbor : a.getNeighbors())
            {
                if(neighbor.getClassification() == Constants::empty)
                {
                    for(Point outerNeighbor : neighbor.getNeighbors())
                    {
                        if(outerNeighbor.getClassification()!=Constants::empty)
                        {
                            canPlace = true;
                        }
                    }
                }
                else
                {
                    canPlace = false;
                }
                
            }
            if(canPlace)
            {
                map[a.getX()][a.getY()].upgrade();
            }
        }
    }
}

void Catan::placeRoad(Point a, Point b, bool isFree)
{
    if(!a.isNeighbor(b))
    {
        if((Constants::empty<=a.getClassification() && a.getClassification()<=Constants::city)&&(Constants::empty<=b.getClassification() && b.getClassification()<=Constants::city))
        {
            if(((a.getOwner() != NULL)&&(b.getOwner() == NULL)) || ((a.getOwner() == NULL)&&(b.getOwner() != NULL)))
            {
                if(a.getOwner() == players[currentTurn] || b.getOwner() == players[currentTurn])
                {
                    a.addNeighbor(b);
                    a.setOwner(players[currentTurn]);

                    b.addNeighbor(a);
                    b.setOwner(players[currentTurn]);
                }
            }
            else if (((a.getOwner() != NULL)&&(b.getOwner() != NULL)) && ((a.getOwner() == b.getOwner())))
            {
                a.addNeighbor(b);
                a.setOwner(players[currentTurn]);

                b.addNeighbor(a);
                b.setOwner(players[currentTurn]);
            }
        }    
    }
}


void Catan::trade(Player *player, int myResource, int otherResource, int myAmount, int otherAmount)
{
    if(players[currentTurn]->canTrade(myAmount,myResource) && player->canTrade(otherAmount,otherResource))
    {
        players[currentTurn]->modifyResources(otherResource,otherAmount);
        players[currentTurn]->modifyResources(myResource,-myAmount);
        player->modifyResources(myResource,myAmount);
        player->modifyResources(otherResource,-otherAmount);
    }
}

void Catan::buyDevelopmentCard()
{
    int roll = 0;
    if(this->knightsCount<3)
    {
        roll = rand() % (Constants::victoryCard - Constants::knight + 1) + Constants::knight;
    }
    else
    {
        roll = rand() % (Constants::victoryCard - Constants::knight + 1) + Constants::knight;
    }
    if(roll==Constants::knight)
    {
        this->knightsCount++;
    }
    players[currentTurn]->modifyResources(roll,1);
}

void Catan::getCurrentPlayerCards()
{
    
}

void Catan::useDevelopmentCard(int card)
{
    switch (card)
    {
    case Constants::monopoly:
        for(Player *player : this->players)
        {
            player->modifyResources(Constants::wood,-player->getResourceCount(Constants::wood)/2);
            this->players[currentTurn]->modifyResources(Constants::wood,player->getResourceCount(Constants::wood)/2);
        }
        break;

    case Constants::pleanty:
        players[currentTurn]->modifyResources(Constants::wood,2);
        break;

    case Constants::builder:
        this->placeRoad(Point(0,0),Point(0,1),true);
        break;
    
    default:
        break;
    }
}

bool Catan::checkVictory()
{
    return this->players[currentTurn]->getVictoryPoints()>=10;
}

void Catan::endTurn()
{
    this->currentTurn = (this->currentTurn+1)%3;
}

void Catan::printMap() const {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 11; ++j) {
            std::cout << std::setw(8);
            switch (map[i][j].getClassification()) {
                case Constants::sea:
                    std::cout << "SEA";
                    break;
                case Constants::empty:
                    std::cout << "EMPTY";
                    break;
                case Constants::iron:
                    std::cout << "IRON";
                    break;
                case Constants::wool:
                    std::cout << "WOOL";
                    break;
                case Constants::wood:
                    std::cout << "WOOD";
                    break;
                case Constants::wheat:
                    std::cout << "WHEAT";
                    break;
                case Constants::brick:
                    std::cout << "BRICK";
                    break;
                case Constants::desert:
                    std::cout << "DESERT";
                    break;
                default:
                    std::cout << "UNKNOWN";
                    break;
            }
        }
        std::cout << std::endl;
    }
}
