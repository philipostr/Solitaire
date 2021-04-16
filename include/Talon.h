#ifndef TALON_H
#define TALON_H

#include "CardPile.h"


class Talon : public CardPile
{
    public:
        Talon();

        bool addCard(Card*);

    private:
};

#endif // TALON_H
