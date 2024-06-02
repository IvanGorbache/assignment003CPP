#include "catan.hpp"

Catan::Catan(Player p1, Player p2, Player p3)
{
    this->players[0] = p1;
    this->players[1] = p2;
    this->players[2] = p3;

    std::fill_n(this->firstTurn, 3, false);
}

Catan::~Catan()
{

}

void Catan::rollDice(int cheat=0)
{
    int roll = cheat;
    if(!cheat)
    {
        roll = rand() % (12 - 2 + 1) + 2;
    } 
    for(Player player : this->players)
    {
        for(Point settlement : player.getSettlements())
        {
            
        }
    }
}

void Catan::placeSettelemnt(Point a)
{
    bool canPlace = false;
    if(a.getClassification() == Constants::empty)
    {
        if(&a.getOwner() == NULL && a.getClassification() == Constants::empty && a.getNeighbors().size()>0)
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
                this->map[a.getX()][a.getY()].upgrade();
            }
        }
    }
}

void Catan::placeRoad(Point a, Point b)
{
    if((Constants::empty<=a.getClassification() && a.getClassification()<=Constants::city)&&(Constants::empty<=b.getClassification() && b.getClassification()<=Constants::city))
    {

    }
}


void Catan::trade(Player player, Constants::type myResource, Constants::type otherResource, int myAmount, int otherAmount)
{
    players[currentTurn].modifyResouces(otherResource,otherAmount);
    player.modifyResouces(myResource,myAmount);

    players[currentTurn].modifyResouces(myResource,-myAmount);
    player.modifyResouces(otherResource,-otherAmount);
}

void Catan::buyDevelopmentCard()
{

}

void Catan::getCurrentPlayerCards()
{
    
}

void Catan::useDevelopmentCard()
{
    
}

bool Catan::checkVictory()
{
    return this->players[currentTurn].getVictoryPoints()>=10;
}

void Catan::endTurn()
{
    this->currentTurn = (this->currentTurn+1)%3;
}
