#include "Talon.h"

Talon::Talon()
{
}

bool Talon::addCard(Card* newCard)
{
    this->cards.push_back(newCard);
    this->cards.back()->switchIsHidden();
    return true;
}
