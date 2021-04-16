#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
    public:
        struct Suit
        {
            std::string suit;
            int color;
        };

        Card(); //Constructs object as Ace of Hearts
        Card(int); //Constructs random card. Input int does not matter
        Card(int, int); //Constructs card with specific suit and rank

        static std::string ranks[13]; //Contains all ranks in order of value
        static Suit suits[4]; //Contains all suits and their colors

        int getRankValue();
        void setRankValue(int);
        int getSuitValue();
        void setSuitValue(int);
        bool getIsHidden();
        void switchIsHidden();
        void setDisplayString();

        Suit compareSuits(Card*); //Returns t/1(true) OR f/0(false) for equality of suit and color between this card and another card
        int compareRanks(Card*); //Returns the int difference of the parameter card's rank compared to this card's

        void display(bool);

    private:
        int rankValue; //Doubles as the card itself's value
        int suitValue;
        bool isHidden; //True if card is face down. Default true
        std::string displayString;
};

#endif // CARD_H
