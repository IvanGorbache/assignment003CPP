#include "card.hpp"
class Builer: public Card
{
public:
    Builer(int type);
    ~Builer();
    virtual void operator()(Player &p, Catan &game);
};