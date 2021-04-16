#ifndef FOUNDATION_H
#define FOUNDATION_H

#include "CardPile.h"


class Foundation : public CardPile
{
    public:
        Foundation(int);

        bool addCard(Card*);

    private:
        int suitValue;
};

#endif // FOUNDATION_H
