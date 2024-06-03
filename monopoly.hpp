#include "card.hpp"
class Monopoly: public Card
{
public:
    Monopoly(int type);
    ~Monopoly();
    virtual void operator()(Player &p, Catan &game);
};