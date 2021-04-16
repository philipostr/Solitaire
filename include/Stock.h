#ifndef STOCK_H
#define STOCK_H

#include "CardPile.h"


class Stock : public CardPile
{
    public:
        Stock();

        bool addCard(Card*);

        void recycle(CardPile*);

    private:
};

#endif // STOCK_H
