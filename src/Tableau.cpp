#include "Tableau.h"

Tableau::Tableau()
{
}

bool Tableau::addCard(Card* newCard)
{
    if (this->cards.size() == 0 && newCard->getRankValue() == 12) //if the tableau is empty and the new card is a king
    {
        this->cards.push_back(newCard);
        return true;
    }
    else if (this->cards.size() > 0 && this->cards.back()->compareRanks(newCard) == -1 && this->cards.back()->compareSuits(newCard).color == 0) //if the new card is next rank and different color
    {
        this->cards.push_back(newCard);
        return true;
    }

    return false;
}

Card* Tableau::takeTopCard()
{
    Card* topCard = this->cards.back();
    if (this->cards.size() > 1 && this->cards.at(this->cards.size() - 2)->getIsHidden())
    {
        this->cards.at(this->cards.size() - 2)->switchIsHidden();
    }
    this->cards.pop_back();
    return topCard;
}
