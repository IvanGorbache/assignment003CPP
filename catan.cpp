#include "catan.hpp"

#include "constants.hpp"

Catan::Catan(Player *p1, Player *p2, Player *p3, bool useDefault, int defaultRoll)
{
    this->players[0] = p1;
    this->players[1] = p2;
    this->players[2] = p3;
    minCard = Constants::knight;
    maxCard = Constants::victoryCard;
    std::fill_n(this->turnCounter, 3, 0);
    std::vector<Point> points;
    int biomCount[] = {1,4,3,3,4,4};
    int rand = 0;
    int originalMap[12][11];
    std::random_device rd;
    std::mt19937 gen(rd());
    if(useDefault)
    {
        int defaultMap[12][11] = 
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
        std::copy(&defaultMap[0][0], &defaultMap[0][0] + 12 * 11, &originalMap[0][0]);
    }
    else
    {
        int tempMap[12][11]= 
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
        std::copy(&tempMap[0][0], &tempMap[0][0] + 12 * 11, &originalMap[0][0]);
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
                    player->modifyResources(p->getClassification(),amount);
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
                        player->modifyResources(i+Constants::wood,-1);
                        discard-=1;
                    }
                    
                }
            }
            player->printer();
        }

    }
}


void Catan::placeSettelemnt(Point a)
{
    bool canPlace = false;
    bool hasNeighbors = false;

    if (map[a.getX()][a.getY()].getClassification() == Constants::empty && (map[a.getX()][a.getY()].getRoads().size() > 0 || turnCounter[currentTurn] < 1))
    {
        if (turnCounter[currentTurn] < 1 && map[a.getX()][a.getY()].getOwner() == nullptr && map[a.getX()][a.getY()].getRoads().size() == 0)
        {
            canPlace = true;
            hasNeighbors = true;
        }
        else
        {
            for (Road road : map[a.getX()][a.getY()].getRoads())
            {
                if (road.getOwner() == players[currentTurn])
                {
                    hasNeighbors = true;
                    Point* end = road.getEnd();

                    if ((end->getClassification() == Constants::settlement && end->getOwner() == players[currentTurn]))
                    {

                        canPlace = false;
                        break;
                    }

                    bool hasTwoRoadsAway = false;

                    for (Road secondRoad : end->getRoads())
                    {
                        std::cout<<secondRoad.toString();
                        if (secondRoad.getOwner() == players[currentTurn])
                        {
                            Point* secondEnd = secondRoad.getEnd();

                            if (secondEnd->getClassification() == Constants::settlement && secondEnd->getOwner() == players[currentTurn])
                            {
                                hasTwoRoadsAway = true;
                                break;
                            }
                        }
                    }

                    if (hasTwoRoadsAway)
                    {
                        canPlace = true;
                        break;
                    }
                }
            }
        }
    }

    if (canPlace && hasNeighbors && ((players[currentTurn]->canTrade(Constants::brick, 1) &&
                      players[currentTurn]->canTrade(Constants::wood, 1) &&
                      players[currentTurn]->canTrade(Constants::wool, 1) &&
                      players[currentTurn]->canTrade(Constants::wheat, 1)) ||
                     turnCounter[currentTurn] < 1))
    {
        map[a.getX()][a.getY()].setOwner(players[currentTurn]);
        map[a.getX()][a.getY()].setClassification(Constants::settlement);
        players[currentTurn]->modifyVictoryPoints(1);
        players[currentTurn]->addSettlements(map[a.getX()][a.getY()]);

        if (!(turnCounter[currentTurn] < 1))
        {
            players[this->currentTurn]->modifyResources(Constants::wood, -1);
            players[this->currentTurn]->modifyResources(Constants::brick, -1);
            players[this->currentTurn]->modifyResources(Constants::wool, -1);
            players[this->currentTurn]->modifyResources(Constants::wheat, -1);
        }
    }
}

void Catan::buildCity(Point a)
{
    std::cout<<"Upgrade";
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
            canPlace = true;
        }
    }
    if(canPlace && ((players[currentTurn]->canTrade(Constants::wood,1)&&players[currentTurn]->canTrade(Constants::brick,1))||turnCounter[currentTurn]<1||isFree))
    {
        if(!a.hasRoad(b) && !b.hasRoad(a))
        {
            if(a.getRoads().size()<3 && b.getRoads().size()<3)
            {
                map[a.getX()][a.getY()].addNeighbor(map[b.getX()][b.getY()]);
                map[b.getX()][b.getY()].addNeighbor(map[a.getX()][a.getY()]);

                if(!(turnCounter[currentTurn]<1||isFree))
                {
                    players[this->currentTurn]->modifyResources(Constants::wood,-1);
                    players[this->currentTurn]->modifyResources(Constants::brick,-1);
                }

                map[a.getX()][a.getY()].addRoad(Road(players[currentTurn],&map[a.getX()][a.getY()],&map[b.getX()][b.getY()]));
                map[b.getX()][b.getY()].addRoad(Road(players[currentTurn],&map[b.getX()][b.getY()],&map[a.getX()][a.getY()]));
            }
        }
    }
}

void Catan::trade(Player *player, int myResource, int otherResource, int myAmount, int otherAmount)
{
    if(players[currentTurn]->canTrade(myResource,myAmount) && player->canTrade(otherResource,otherAmount))
    {
        
        if(myResource==Constants::knight)
        {
            if( players[currentTurn]->getResourceCount(Constants::knight)==3)
            {
                players[currentTurn]->modifyVictoryPoints(-2);
            }
            if(player->getResourceCount(Constants::knight)+myAmount==3)
            {
                player->modifyVictoryPoints(2);
            }
        }

        if(otherResource==Constants::knight)
        {
            if(player->getResourceCount(Constants::knight)==3)
            {
                player->modifyVictoryPoints(-2);
            }
            if(players[currentTurn]->getResourceCount(Constants::knight)+otherAmount==3)
            {
                players[currentTurn]->modifyVictoryPoints(2);
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

        players[currentTurn]->printer();
        player->printer();
    }
}

void Catan::buyDevelopmentCard(int choice)
{
    if(players[currentTurn]->canTrade(Constants::iron,1),players[currentTurn]->canTrade(Constants::wool,1),players[currentTurn]->canTrade(Constants::wheat,1))
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minCard, maxCard);
        int roll = choice;
        if (choice == 0)
        {
            roll = dis(gen);
        }
        
        if(roll==Constants::knight)
        {
            this->knightsCount++;
            if(knightsCount==3)
            {
                players[currentTurn]->modifyVictoryPoints(2);
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
        players[currentTurn]->modifyResources(Constants::wheat,-1);
        players[currentTurn]->modifyResources(Constants::wool,-1);
        players[currentTurn]->modifyResources(Constants::iron,-1);
        
    }
}

void Catan::useDevelopmentCard(int card,int resource,int x1, int y1,int u1,int v1,int x2, int y2,int u2,int v2)
{
    if(players[currentTurn]->canTrade(card,1))
    {
        switch (card)
            {
            case Constants::monopoly:
                for(Player *player : this->players)
                {
                    if(player!=players[currentTurn])
                    {
                        this->players[currentTurn]->modifyResources(resource,player->getResourceCount(resource)/2);
                        player->modifyResources(resource,-player->getResourceCount(resource)/2);

                    }
                }
                break;

            case Constants::pleanty:
                players[currentTurn]->modifyResources(resource,2);
                break;

            case Constants::builder:
                this->placeRoad(Point(x1,y1),Point(u1,v1),true);
                this->placeRoad(Point(x2,y2),Point(u2,v2),true);
                break;
            
            default:
                break;
            }
        players[currentTurn]->modifyResources(card,-1);

    }
}

bool Catan::checkVictory()
{
    return this->players[currentTurn]->getVictoryPoints()>=10;
}

void Catan::endTurn()
{
    this->turnCounter[currentTurn]++;
    this->currentTurn = (this->currentTurn+1)%3;
    std::cout<<players[currentTurn]->getName()<<"'s TURN:"<<std::endl;
}

void Catan::printMap() const {
    const int cellWidth = 1;
    std::string owner;

    for (int i = 0; i < 12; ++i) {
        // Adjust spacing for staggered rows

        for (int j = 0; j < 11; ++j) {
            std::cout << std::setw(cellWidth);
           
            if (map[i][j].getOwner() != nullptr) {
                owner = map[i][j].getOwner()->getName();
            } else {
                owner = std::string(1, ' '); 
            }

            std::cout << "(" << i << "," << j << ") " << Constants::gameResourceIcons[map[i][j].getClassification()] << "-" << map[i][j].getId() << "-" << owner << " ";       
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 11; ++j) {
            for(Road road:map[i][j].getRoads())
            {
                std::cout<<road.toString()<<std::endl;
            }
        }
    }
}

Point Catan::GetPoint(int x, int y) const
{
    return map[x][y];
}

Player* Catan::getPlayer(int index) const
{
    return this->players[index];
}
