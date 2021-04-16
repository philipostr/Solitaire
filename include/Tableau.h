#ifndef TABLEAU_H
#define TABLEAU_H

#include "CardPile.h"


class Tableau : public CardPile
{
    public:
        Tableau();

        bool addCard(Card*);
        Card* takeTopCard();

    private:
};

#endif // TABLEAU_H
