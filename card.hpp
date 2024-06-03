#include "catan.hpp"
class Card
{
private:
    int cardType;
public:
    Card(int cardType);
    ~Card();
    virtual void operator()(Player &p, Catan &game);
    int getCardType();
};
