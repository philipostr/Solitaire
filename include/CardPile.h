#ifndef CARDPILE_H
#define CARDPILE_H

#include <vector>
#include "Card.h"

class CardPile
{
    public:
        CardPile();

        void initPush(Card*);
        void operator=(CardPile*);

        virtual bool addCard(Card*) = 0;
        virtual Card* takeTopCard();
        std::vector<Card*>* getCards();

        void shuffle();
        void recycle(CardPile*);
        bool addPile(CardPile*, int);

    protected:
        std::vector<Card*> cards;
};

#endif // CARDPILE_H
