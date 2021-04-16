#include "Player.h"

#include <iostream>

Player::Player(std::string newName)
{
    this->points = 0;
    this->name = newName;
    for (int i = 1; i <= 7; i++)
    {
        this->tableaus[i - 1] = new Tableau;
    }
    for (int i = 0; i < 4; i++) this->foundations[i] = new Foundation(i);
    this->stock = new Stock;
    this->talon = new Talon;
}

Player::~Player()
{
    //dtor
}

void Player::deal(CardPile* deck)
{
    std::vector<Card*>* deckCards = deck->getCards();
    int iterater = 0;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            this->tableaus[i]->getCards()->push_back(new Card(deckCards->at(iterater)->getRankValue(), deckCards->at(iterater)->getSuitValue()));
            iterater++;
        }
        this->tableaus[i]->getCards()->back()->switchIsHidden();
    }
    for (int i = iterater; i < 52; i++)
    {
        this->stock->getCards()->push_back(new Card(deckCards->at(i)->getRankValue(), deckCards->at(i)->getSuitValue()));
    }

    return;
}

void Player::display(bool showName)
{
    if (showName)
    {
        std::cout << this->name << "'s Turn\n\n\n";
    }

    std::cout << "Stock: ";
    if (this->stock->getCards()->size() == 0)
    {
        std::cout << "Must recycle.";
    }
    else
    {
        std::cout << this->stock->getCards()->size() << " cards left.";
    }
    std::cout << std::endl;

    std::cout << "Talon: ";
    if (this->talon->getCards()->size() == 0)
    {
        std::cout << "Empty.";
    }
    else
    {
        this->talon->getCards()->back()->display(false);
    }
    std::cout << std::endl << std::endl;

    std::cout << "                          (a)                        (b)                        (c)                        (d)                        (e)                        (f)                        (g)           \n";
    for (int i = 1; i <= 14; i++)
    {
        if (i < 10)
        {
            std::cout << "              " << i;
        }
        else
        {
            std::cout << "             " << i;
        }

        for (int j = 0; j < 7; j++)
        {
            if (this->tableaus[j]->getCards()->size() >= i)
            {
                this->tableaus[j]->getCards()->at(i - 1)->display(true);
            }
            else
            {
                std::cout << "                         ";
            }
            if (i < 10)
            {
                std::cout << " " << i;
            }
            else
            {
                std::cout << i;
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << std::endl << Card::suits[i].suit << ": ";
        if (this->foundations[i]->getCards()->size() == 0)
        {
            std::cout << "Empty.";
        }
        else
        {
            this->foundations[i]->getCards()->back()->display(false);
        }
    }
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "What is your move? (Type 'help' for full list of commands) ";
}

std::string Player::getName()
{
    return this->name;
}

CardPile** Player::getTableaus()
{
    return this->tableaus;
}

CardPile* Player::getStock()
{
    return this->stock;
}

CardPile** Player::getFoundations()
{
    return this->foundations;
}

CardPile* Player::getTalon()
{
    return this->talon;
}

void Player::givePoint()
{
    this->points++;
    return;
}

int Player::getPoints()
{
    return this->points;
}


