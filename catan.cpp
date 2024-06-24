#include "catan.hpp"

#include "constants.hpp"

Catan::Catan(Player *p1, Player *p2, Player *p3, bool useDefault, int defaultRoll)
{
    this->players[0] = p1;
    this->players[1] = p2;
    this->players[2] = p3;
    minCard = Constants::knight;
    maxCard = Constants::victoryCard;
    std::fill_n(this->tutnCounter, 3, 0);
    std::vector<Point> points;
    int biomCount[] = {1,4,3,3,4,4};
    int rand = 0;
    int originalMap[12][11];
    std::random_device rd;
    std::mt19937 gen(rd());
    if(useDefault)
    {
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
    }
    else
    {
        int originalMap[12][11]= 
        {
            {Constants::sea, Constants::sea, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::sea, Constants::sea},
            {Constants::sea, Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea, Constants::sea},
            {Constants::sea, Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea, Constants::sea},
            {Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea},
            {Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea},
            {Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty},
            {Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty},
            {Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea},
            {Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea},
            {Constants::sea, Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea, Constants::sea},
            {Constants::sea, Constants::sea, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::temp, Constants::empty, Constants::sea, Constants::sea},
            {Constants::sea, Constants::sea, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::empty, Constants::sea, Constants::sea, Constants::sea},
        };
        for(int i = 1;i<12;i+=2)
        {
            for(int j = 0;j<11;j++)
            {
                if(originalMap[i][j]==Constants::temp)
                {
                    points.push_back(Point(i,j));
                }
            }
        }        
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < biomCount[i]; j++)
            {
                std::uniform_int_distribution<> dis(0, points.size()-1);
                rand = dis(gen);
                originalMap[points[rand].getX()][points[rand].getY()] = i + Constants::desert;
                originalMap[points[rand].getX()+1][points[rand].getY()] = i + Constants::desert;
                points.erase(points.begin()+rand);
            }        
        }
    }

    std::uniform_int_distribution<> dis(1, 12);
    for(int i = 0;i<12;i++)
    {
        for(int j = 0;j<11;j++)
        {
            if(Constants::wood<=originalMap[i][j] && originalMap[i][j]<=Constants::wool )
            {
                if(originalMap[i][j] == originalMap[i-1][j])
                {
                    map[i][j] = map[i-1][j];
                }
                else
                {
                    if(useDefault)
                    {
                        rand = defaultRoll;
                    }
                    else
                    {
                        rand = dis(gen);
                    }
                    map[i][j] = Point(rand,i,j,originalMap[i][j]);
                }
            }
            else
            {
                map[i][j] = Point(0,i,j,originalMap[i][j]);
            }
        }
    }
}
Catan::~Catan()
{

}

void Catan::rollDice(int cheat)
{
    Point* area[4];
    int x, y, discard;
    int roll = cheat, amount = 0;
    std::random_device r1;
    std::mt19937 gen1(r1());
    std::uniform_int_distribution<> dis(1, 6);
    if (cheat==0)
    {
        roll = dis(gen1)+dis(gen1);
    }
    std::cout<<roll;

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
                    player->modifyResources(p->getClassification()+Constants::wood,amount);
                }
            }
        }
        player->printer();
    }
    if (roll==7)
    {
        for (Player *player : this->players)
        {
            if(player->getTotalResources()>=7)
            {
                discard = player->getTotalResources()/2;
                for(int i = 0;i<Constants::inventorySize;i++)
                {
                    while (discard>0 && player->getResourceCount(i+Constants::wood)>0)
                    {
                        player->modifyResources(i+Constants::wood,-i);
                    }
                    
                }
            }
        }
    }
}


void Catan::placeSettelemnt(Point a)
{
    bool canPlace = true;
    if((map[a.getX()][a.getY()].getOwner() == NULL || map[a.getX()][a.getY()].getOwner() == players[currentTurn]) && map[a.getX()][a.getY()].getClassification() == Constants::empty && (map[a.getX()][a.getY()].getNeighbors().size()>0 || tutnCounter[currentTurn]<1))
    {
        for(Point neighbor : map[a.getX()][a.getY()].getNeighbors())
        {
            if((neighbor.getClassification() == Constants::empty) && (neighbor.getOwner() == map[a.getX()][a.getY()].getOwner()))
            {
                for(Point outerNeighbor : neighbor.getNeighbors())
                {
                    if(outerNeighbor.getClassification()!=Constants::empty && (outerNeighbor.getOwner() == map[a.getX()][a.getY()].getOwner()))
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
    }
    else
    {
        canPlace = false;
    }
    
    if(canPlace && ((players[currentTurn]->canTrade(Constants::brick,1) && players[currentTurn]->canTrade(Constants::wood,1) && players[currentTurn]->canTrade(Constants::wool,1)&& players[currentTurn]->canTrade(Constants::wheat,1)) || tutnCounter[currentTurn]<1))
    {
        map[a.getX()][a.getY()].setOwner(players[currentTurn]);
        map[a.getX()][a.getY()].upgrade();
        players[currentTurn]->modifyVictoryPoints(1);
        players[currentTurn]->addSettlements(map[a.getX()][a.getY()]);
        if(!(tutnCounter[currentTurn]<1))
        {
            players[this->currentTurn]->modifyResources(Constants::wood,-1);
            players[this->currentTurn]->modifyResources(Constants::brick,-1);
            players[this->currentTurn]->modifyResources(Constants::wool,-1);
            players[this->currentTurn]->modifyResources(Constants::wheat,-1);
        }
    }
}

void Catan::buildCity(Point a)
{
    if(map[a.getX()][a.getY()].getOwner() == players[currentTurn] && map[a.getX()][a.getY()].getClassification()==Constants::settlement&& players[currentTurn]->canTrade(Constants::iron,3)&& players[currentTurn]->canTrade(Constants::wheat,2))
    {
        map[a.getX()][a.getY()].upgrade();
        players[currentTurn]->modifyVictoryPoints(1);
        players[this->currentTurn]->modifyResources(Constants::iron,-3);
        players[this->currentTurn]->modifyResources(Constants::wheat,-2);
    }
}

void Catan::placeRoad(Point a, Point b, bool isFree)
{
    bool canPlace = false;
    if(!map[a.getX()][a.getY()].isNeighbor(map[b.getX()][b.getY()]))
    {
        if((Constants::empty<=map[a.getX()][a.getY()].getClassification() && map[a.getX()][a.getY()].getClassification()<=Constants::city)&&(Constants::empty<=map[b.getX()][b.getY()].getClassification() && map[b.getX()][b.getY()].getClassification()<=Constants::city))
        {
            if(((map[a.getX()][a.getY()].getOwner() != NULL)&&(map[b.getX()][b.getY()].getOwner() == NULL)) || ((map[a.getX()][a.getY()].getOwner() == NULL)&&(map[b.getX()][b.getY()].getOwner() != NULL)))
            {
                canPlace = true;
            }
            else if (((map[a.getX()][a.getY()].getOwner() != NULL)&&(map[b.getX()][b.getY()].getOwner() != NULL)) && ((map[a.getX()][a.getY()].getOwner() == map[b.getX()][b.getY()].getOwner())))
            {
                canPlace = true;
                
            }
        }    
    }
    if(canPlace && ((players[currentTurn]->canTrade(Constants::wood,1)&&players[currentTurn]->canTrade(Constants::brick,1))||tutnCounter[currentTurn]<1||isFree))
    {
        map[a.getX()][a.getY()].addNeighbor(map[b.getX()][b.getY()]);

        map[b.getX()][b.getY()].addNeighbor(map[a.getX()][a.getY()]);

        if(!(tutnCounter[currentTurn]<1||isFree))
        {
            players[this->currentTurn]->modifyResources(Constants::wood,-1);
            players[this->currentTurn]->modifyResources(Constants::brick,-1);
        }

        if((map[a.getX()][a.getY()].getOwner() != NULL)&&(map[b.getX()][b.getY()].getOwner() == NULL))
        {
            map[b.getX()][b.getY()].setOwner(map[a.getX()][a.getY()].getOwner());
        }
        else if((map[a.getX()][a.getY()].getOwner() == NULL)&&(map[b.getX()][b.getY()].getOwner() != NULL))
        {
            map[a.getX()][a.getY()].setOwner(map[b.getX()][b.getY()].getOwner());
        }
    }
}


void Catan::trade(Player *player, int myResource, int otherResource, int myAmount, int otherAmount)
{
    if(players[currentTurn]->canTrade(myAmount,myResource) && player->canTrade(otherAmount,otherResource))
    {
        if(myResource==Constants::knight && players[currentTurn]->getResourceCount(Constants::knight)==3)
        {
            players[currentTurn]->modifyVictoryPoints(-1);
            if(player->getResourceCount(Constants::knight)+myResource==3)
            {
                player->modifyVictoryPoints(1);
            }
        }

        if(otherResource==Constants::knight && player->getResourceCount(Constants::knight)==3)
        {
            player->modifyVictoryPoints(-1);
            if(players[currentTurn]->getResourceCount(Constants::knight)+otherAmount==3)
            {
                players[currentTurn]->modifyVictoryPoints(1);
            }
        }

        if(myResource==Constants::victoryCard)
        {
            players[currentTurn]->modifyVictoryPoints(-myAmount);
            player->modifyVictoryPoints(myAmount);
        }

        if(otherResource==Constants::victoryCard)
        {
            player->modifyVictoryPoints(-otherAmount);
            players[currentTurn]->modifyVictoryPoints(otherAmount);
        }
        
        players[currentTurn]->modifyResources(otherResource,otherAmount);
        players[currentTurn]->modifyResources(myResource,-myAmount);
        player->modifyResources(myResource,myAmount);
        player->modifyResources(otherResource,-otherAmount);


    }
}

void Catan::buyDevelopmentCard()
{
    if(players[currentTurn]->canTrade(Constants::iron,1),players[currentTurn]->canTrade(Constants::wool,1),players[currentTurn]->canTrade(Constants::wheat,1))
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minCard, maxCard);
        int roll = dis(gen);
        if(roll==Constants::knight)
        {
            this->knightsCount++;
            if(knightsCount==3)
            {
                players[currentTurn]->modifyVictoryPoints(1);
                minCard++;
            }
        }
        if (roll==Constants::victoryCard)
        {
            this->victoryCardCount++;
            players[currentTurn]->modifyVictoryPoints(1);
            if (victoryCardCount==5)
            {
                maxCard--;
            }
        }
        players[currentTurn]->modifyResources(roll,1);
        
    }
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
    this->tutnCounter[currentTurn]++;
    this->currentTurn = (this->currentTurn+1)%3;
}

void Catan::printMap() const {
    std::string owner;
    const int cellWidth = 5; 
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 11; ++j) {
            std::cout << std::setw(cellWidth);
            owner = map[i][j].getOwner() != nullptr ? map[i][j].getOwner()->getName() : "";
            std::cout << Constants::gameResourceIcons[map[i][j].getClassification()] << "-" << map[i][j].getId() << "-" << owner;
        }
        std::cout << std::endl;
    }
}
