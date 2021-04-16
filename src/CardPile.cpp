#include "CardPile.h"

#include <iostream>
#include <ctime>

CardPile::CardPile()
{
}

void CardPile::initPush(Card* newCard)
{
    this->cards.push_back(newCard);
    return;
}

void CardPile::operator=(CardPile* otherPile)
{
    this->cards = *(otherPile->getCards());

    return;
}

Card* CardPile::takeTopCard()
{
    Card* topCard = this->cards.back();
    this->cards.pop_back();
    return topCard;
}

std::vector<Card*>* CardPile::getCards()
{
    return &(this->cards);
}

void CardPile::shuffle()
{
    srand(time(NULL));
    int temp1, temp2;
    Card* tempCard;

    for (int i = 0; i < 10000; i++)
    {
        temp1 = rand() % 52;
        temp2 = rand() % 52;
        while (temp1 == temp2)
        {
            temp2 = rand() % 52;
        }
        tempCard = this->cards.at(temp1);
        this->cards.at(temp1) = this->cards.at(temp2);
        this->cards.at(temp2) = tempCard;
    }

    return;
}

void CardPile::recycle(CardPile* talon)
{
    std::vector<Card*>* talonCards = talon->getCards();
    int initialSize = talonCards->size();

    this->cards = *talonCards;
    for (int i = 0; i < initialSize; i++)
    {
        this->cards.at(i)->switchIsHidden();
        talonCards->pop_back();
    }

    return;
}

bool CardPile::addPile(CardPile* oldTableau, int startIndex)
{
    std::vector<Card*>* oldCards = oldTableau->getCards();
    int originalSize = oldCards->size();

    if (this->addCard(oldCards->at(startIndex)))
    {
        for (int i = startIndex + 1; i < originalSize; i++)
        {
            this->cards.push_back(oldCards->at(i));
        }
        for (int i = startIndex; i < originalSize; i++)
        {
            oldTableau->takeTopCard();
        }

        if (oldCards->size() > 0 && oldCards->back()->getIsHidden())
        {
            oldCards->back()->switchIsHidden();
        }
        return true;
    }

    return false;
}


