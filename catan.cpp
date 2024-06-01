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

void Catan::rollDice()
{
    int roll = rand() % (12 - 2 + 1) + 2;
    Point pointOfIntrest;
    for(Player player : this->players)
    {
        for(Intersection settlement : player.getSettlements())
        {
            if(Land* land = dynamic_cast<Land*>(&this->gameboard.getPointAt(settlement.getX(),settlement.getY())))
            {
                if(land->getId() == roll)
                {
                    player.modifyResouces(land->getResource(),settlement.getStatus());
                }
            }
        }
    }
}

void Catan::placeSettelemnt(Point a)
{
    bool canPlace = false;
    if(Intersection* pointOfIntrest = dynamic_cast<Intersection*>(&this->gameboard.getPointAt(a.getX(),a.getY())))
    {
        if(pointOfIntrest->getOwner() == NULL && pointOfIntrest->getStatus() == Constants::empty && pointOfIntrest->geteighbors().size()>0)
        {
            for(Intersection neighbor : pointOfIntrest->geteighbors())
            {
                if(neighbor.getStatus() == Constants::empty)
                {
                    for(Intersection outerNeighbor : neighbor.geteighbors())
                    {
                        if(outerNeighbor.getStatus()!=Constants::empty)
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
                this->gameboard.placeSettlement(this->players[this->currentTurn],a);
            }
        }
    }
}

void Catan::placeRoad(Point a, Point b)
{
    if(Intersection* start = dynamic_cast<Intersection*>(&this->gameboard.getPointAt(a.getX(),a.getY())))
    {
        if(Intersection* end = dynamic_cast<Intersection*>(&this->gameboard.getPointAt(b.getX(),b.getY())))
        {
            if((start->getOwner() == this->players[currentTurn] && end->getOwner() == NULL) || (start->getOwner() == NULL && end->getOwner() == this->players[currentTurn]))
            {
                start->addNeighbor(*end);
                end->addNeighbor(*start);
            }
            else if((start->getOwner() == this->players[currentTurn] && end->getOwner() == this->players[currentTurn]) && !start->isNeighbor(*end))
            {
                start->addNeighbor(*end);
                end->addNeighbor(*start);
            }
        }
    }
}


void Catan::trade(Player player, Constants::resource myResource, Constants::resource otherResource, int myAmount, int otherAmount)
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