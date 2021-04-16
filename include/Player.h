#ifndef PLAYER_H
#define PLAYER_H

#include "Foundation.h"
#include "Stock.h"
#include "Tableau.h"
#include "Talon.h"

class Player
{
    public:
        Player(std::string);
        ~Player();

        void deal(CardPile*);

        void display(bool);

        std::string getName();
        CardPile** getTableaus();
        CardPile* getStock();
        CardPile** getFoundations();
        CardPile* getTalon();
        void givePoint();
        int getPoints();

    private:
        std::string name;
        int points;
        CardPile* tableaus[7];
        CardPile* foundations[4];
        CardPile* stock;
        CardPile* talon;
};

#endif // PLAYER_H
