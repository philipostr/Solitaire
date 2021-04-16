#include "Card.h"

#include <ctime>
#include <iostream>
#include <windows.h>

std::string Card::ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
Card::Suit Card::suits[4] = {{"Hearts", 12}, {"Diamonds", 12}, {"Clubs", 11}, {"Spades", 11}};

Card::Card()
{
    this->rankValue = 0;
    this->suitValue = 0;
    this->isHidden = true;
    this->setDisplayString();
}

Card::Card(int dummy)
{
    srand(time(NULL));

    this->rankValue = rand() % 13;
    this->suitValue = rand() % 4;
    this->isHidden = true;
    this->setDisplayString();
}

Card::Card(int newRank, int newSuit)
{
    this->rankValue = newRank;
    this->suitValue = newSuit;
    this->isHidden = true;
    this->setDisplayString();
}

int Card::getRankValue()
{
    return this->rankValue;
}

void Card::setRankValue(int newRank)
{
    this->rankValue = newRank;

    return;
}

int Card::getSuitValue()
{
    return this->suitValue;
}

void Card::setSuitValue(int newSuit)
{
    this->suitValue = newSuit;

    return;
}

bool Card::getIsHidden()
{
    return this->isHidden;
}

void Card::switchIsHidden()
{
    this->isHidden = !this->isHidden;

    return;
}

void Card::setDisplayString()
{
        this->displayString = Card::ranks[this->rankValue] + " of " + Card::suits[this->suitValue].suit;
        float leftSpace = (25 - this->displayString.length()) / 2.0;
        for (int i = 0; i < (int)leftSpace; i++)
        {
            this->displayString = " " + this->displayString;
        }
        for (int i = 0; i < leftSpace * 2 - (int)leftSpace; i++)
        {
            this->displayString = this->displayString + " ";
        }

        return;
}

Card::Suit Card::compareSuits(Card* comparingCard)
{
    Suit comparisons;

    if (Card::suits[this->suitValue].suit == Card::suits[comparingCard->getSuitValue()].suit)
        comparisons.suit = "t";
    else
        comparisons.suit = "f";
    if (Card::suits[this->suitValue].color == Card::suits[comparingCard->getSuitValue()].color)
        comparisons.color = 1;
    else
        comparisons.color = 0;

    return comparisons;
}

int Card::compareRanks(Card* comparingCard)
{
    return comparingCard->getRankValue() - this->rankValue;
}

void Card::display(bool withSpace)
{
    if (!this->isHidden)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Card::suits[this->suitValue].color);
        if (withSpace)
        {
            std::cout << this->displayString;
        }
        else
        {
            std::cout << Card::ranks[this->rankValue] + " of " + Card::suits[this->suitValue].suit;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else
    {
        if (withSpace)
        {
            std::cout << "       Hidden Card       ";
        }
        else
        {
            std::cout << "Hidden Card";
        }
    }

    return;
}
