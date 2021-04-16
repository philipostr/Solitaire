#include "Deck.h"

#include <ctime>

Deck::Deck()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            this->cards.push_back(new Card(j, i));
        }
    }
}

Deck::~Deck()
{
    for (int i = 0; i < 52; i++)
    {
        delete this->cards.back();
        this->cards.pop_back();
    }
}

bool Deck::addCard(Card* card)
{
    return true;
}
