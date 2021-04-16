#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"

class Game
{
    public:
        Game();
        ~Game();

        void run();

        void setup();
        void events();
        void targetEvents(std::string, CardPile*);
        void draw();
        void switchPlayer();
        void comparePlayers();
        void help();

        bool intErrorCatch(std::string);
        bool validMove(std::string);

    private:
        int moves;
        int currentPlayer[2];
        int activePlayers;
        std::vector<Player*> players;
        std::vector<bool> stillIn;
        std::vector<bool> playersCompleted;
        CardPile* deck;
        bool gameFinished;
        bool endGame;
};

#endif // GAME_H
