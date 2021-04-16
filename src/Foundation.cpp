#include "Foundation.h"

Foundation::Foundation(int suit)
{
    this->suitValue = suit;
}

bool Foundation::addCard(Card* newCard)
{
    if (newCard->getSuitValue() == this->suitValue)
    {
        if (this->cards.size() == 0 && newCard->getRankValue() == 0)
        {
            this->cards.push_back(newCard);
            return true;
        }
        else if (this->cards.size() > 0 && this->cards.back()->compareRanks(newCard) == 1)
        {
            this->cards.push_back(newCard);
            return true;
        }
    }

    return false;
}
