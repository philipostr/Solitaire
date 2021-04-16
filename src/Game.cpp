#include "Game.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

Game::Game()
{
    this->deck = new Deck;
    this->gameFinished = false;
}

Game::~Game()
{
    //dtor
}

void Game::run()
{
    std::string response;

    system("cls");
    this->setup();
    while (!(this->gameFinished))
    {
        system("cls");
        if (!endGame)
        {
            this->draw();
        }
        else
        {
            this->comparePlayers();
            this->gameFinished = true;
        }
    }

    return;
}

void Game::setup()
{
    std::string input;
    bool keepGoing = false;

    this->endGame = false;
    this->moves = 0;
    this->currentPlayer[0] = 0;
    this->deck->shuffle();

    do
    {
        system("cls");
        std::cout << "How many players? ";
        std::cin >> input;
        if (!intErrorCatch(input) || std::stoi(input) < 1 || std::stoi(input) > 4)
        {
            std::cout << "\nYou must input an integer between 1 and 4. Press anything...";
            getch();
        }
        else
        {
            keepGoing = true;
        }
    } while (!keepGoing);

    system("cls");
    std::cin.ignore();
    this->currentPlayer[1] = std::stoi(input);
    this->activePlayers = this->currentPlayer[1];
    if (this->currentPlayer[1] > 1)
    {
        for (int i = 1; i <= this->currentPlayer[1]; i++)
        {
            std::cout << "Player " << i << " Name: ";
            std::getline(std::cin, input);
            this->players.push_back(new Player(input));
            this->players.at(i - 1)->deal(this->deck);
            this->stillIn.push_back(true);
            this->playersCompleted.push_back(false);
        }
    }
    else
    {
        this->players.push_back(new Player("Only Player"));
        this->players.back()->deal(this->deck);
        this->stillIn.push_back(true);
        this->playersCompleted.push_back(false);
    }

    return;
}

void Game::events()
{
    std::string input;
    CardPile* accessedPile;

    if (this->players.at(this->currentPlayer[0])->getFoundations()[0]->getCards()->size() == 13 && this->players.at(this->currentPlayer[0])->getFoundations()[1]->getCards()->size() == 13 && this->players.at(this->currentPlayer[0])->getFoundations()[2]->getCards()->size() == 13 && this->players.at(this->currentPlayer[0])->getFoundations()[3]->getCards()->size() == 13)
    {
        this->stillIn.at(this->currentPlayer[0]) = false;
        this->playersCompleted.at(this->currentPlayer[0]) = true;
        this->activePlayers--;
        return;
    }
    std::cin >> input;
    if (input == "help")
    {
        this->help();
    }
    else if (input == "stock" || input == "Stock" || input == "STOCK")
    {
        accessedPile = this->players.at(currentPlayer[0])->getStock();
        if (accessedPile->getCards()->size() == 0)
        {
            accessedPile->recycle(this->players.at(this->currentPlayer[0])->getTalon());
        }
        else
        {
            this->players.at(this->currentPlayer[0])->getTalon()->addCard(accessedPile->takeTopCard());
            this->players.at(this->currentPlayer[0])->givePoint();
        }
    }
    else if (input == "talon" || input == "Talon" || input == "TALON")
    {
        accessedPile = this->players.at(this->currentPlayer[0])->getTalon();
        if (accessedPile->getCards()->size() != 0)
        {
            this->targetEvents("talon", accessedPile);
        }
        else
        {
            std::cout << "\nYou cannot take from an empty talon. Press anything...";
            getch();
        }
    }
    else if (input.length() == 2 || input.length() == 3)
    {
        if (this->intErrorCatch(input.substr(1, input.length() - 1)))
        {
            if (input[0] >= 'a' && input[0] <= 'g')
            {
                this->targetEvents(input, this->players.at(this->currentPlayer[0])->getTableaus()[input[0] - 'a']);
            }
        }
        else
        {
            std::cout << "\n\nInvalid input. Press anything...";
            getch();
        }
    }
    else if (input == "hearts" || input == "Hearts" || input == "HEARTS")
    {
        accessedPile = this->players.at(this->currentPlayer[0])->getFoundations()[0];
        if (accessedPile->getCards()->size() != 0)
        {
            this->targetEvents("hearts", accessedPile);
        }
        else
        {
            std::cout << "\nYou cannot take from an empty foundation. Press anything...";
            getch();
        }
    }
    else if (input == "diamonds" || input == "Diamonds" || input == "DIAMONDS")
    {
        accessedPile = this->players.at(this->currentPlayer[0])->getFoundations()[1];
        if (accessedPile->getCards()->size() != 0)
        {
            this->targetEvents("diamonds", accessedPile);
        }
        else
        {
            std::cout << "\nYou cannot take from an empty foundation. Press anything...";
            getch();
        }
    }
    else if (input == "clubs" || input == "Clubs" || input == "CLUBS")
    {
        accessedPile = this->players.at(this->currentPlayer[0])->getFoundations()[2];
        if (accessedPile->getCards()->size() != 0)
        {
            this->targetEvents("clubs", accessedPile);
        }
        else
        {
            std::cout << "\nYou cannot take from an empty foundation. Press anything...";
            getch();
        }
    }
    else if (input == "spades" || input == "Spades" || input == "SPADES")
    {
        accessedPile = this->players.at(this->currentPlayer[0])->getFoundations()[3];
        if (accessedPile->getCards()->size() != 0)
        {
            this->targetEvents("spades", accessedPile);
        }
        else
        {
            std::cout << "\nYou cannot take from an empty foundation. Press anything...";
            getch();
        }
    }
    else if (input == "fail" || input == "Fail" || input == "FAIL")
    {
        this->stillIn.at(this->currentPlayer[0]) = false;
        this->activePlayers--;
        this->switchPlayer();
    }
    else
    {
        std::cout << "\nUnrecognized command. Press anything...";
        getch();
    }

    return;
}

void Game::targetEvents(std::string accessInput, CardPile* accessPile)
{
    std::string targetInput;

    std::cout << "\n\nWhere would you like to target? ";
    std::cin >> targetInput;

    if (targetInput == "help" || targetInput == "Help" || targetInput == "HELP")
    {
        this->help();
    }
    else if ((accessInput.length() == 2 || accessInput.length() == 3) && std::stoi(accessInput.substr(1, accessInput.length() - 1)) != accessPile->getCards()->size())
    {
        if (std::stoi(accessInput.substr(1, accessInput.length() - 1)) <= accessPile->getCards()->size() && std::stoi(accessInput.substr(1, accessInput.length() - 1)) > 0 && !(accessPile->getCards()->at(std::stoi(accessInput.substr(1, accessInput.length() - 1)) - 1)->getIsHidden()))
        {
            if (targetInput.length() == 1 && targetInput[0] >= 'a' && targetInput[0] <= 'g')
            {
                if (!(this->players.at(this->currentPlayer[0])->getTableaus()[targetInput[0] - 'a']->addPile(accessPile, std::stoi(accessInput.substr(1, accessInput.length() - 1)) - 1)))
                {
                    std::cout << "\n\nYou cannot do this. Press anything... ";
                    getch();
                }
                else
                {
                    this->players.at(this->currentPlayer[0])->givePoint();
                    this->moves++;
                }
            }
            else
            {
                std::cout << "\n\n'" << targetInput << "' is not a valid target. Press anything...";
                getch();
            }
        }
        else
        {
            std::cout << "\n\nCannot access that card. Press anything...";
            getch();
        }
    }
    else if (targetInput.length() == 1 && targetInput[0] >= 'a' && targetInput[0] <= 'g')
    {
        if (this->players.at(this->currentPlayer[0])->getTableaus()[targetInput[0] - 'a']->addCard(accessPile->getCards()->back()))
        {
            accessPile->takeTopCard();
            this->players.at(this->currentPlayer[0])->givePoint();
            this->moves++;
        }
        else
        {
            std::cout << "\n\nYou cannot add that card there. Press anything...";
            getch();
        }
    }
    else if (targetInput == "hearts")
    {
        if (this->players.at(this->currentPlayer[0])->getFoundations()[0]->addCard(accessPile->getCards()->back()))
        {
            accessPile->takeTopCard();
            this->moves++;
            this->players.at(this->currentPlayer[0])->givePoint();
        }
        else
        {
            std::cout << "\n\nYou cannot add that card there. Press anything...";
            getch();
        }
    }
    else if (targetInput == "diamonds")
    {
        if (this->players.at(this->currentPlayer[0])->getFoundations()[1]->addCard(accessPile->getCards()->back()))
        {
            accessPile->takeTopCard();
            this->moves++;
            this->players.at(this->currentPlayer[0])->givePoint();
        }
        else
        {
            std::cout << "\n\nYou cannot add that card there. Press anything...";
            getch();
        }
    }
    else if (targetInput == "clubs")
    {
        if (this->players.at(this->currentPlayer[0])->getFoundations()[2]->addCard(accessPile->getCards()->back()))
        {
            accessPile->takeTopCard();
            this->moves++;
            this->players.at(this->currentPlayer[0])->givePoint();
        }
        else
        {
            std::cout << "\n\nYou cannot add that card there. Press anything...";
            getch();
        }
    }
    else if (targetInput == "spades")
    {
        if (this->players.at(this->currentPlayer[0])->getFoundations()[3]->addCard(accessPile->getCards()->back()))
        {
            accessPile->takeTopCard();
            this->moves++;
            this->players.at(this->currentPlayer[0])->givePoint();
        }
        else
        {
            std::cout << "\n\nYou cannot add that card there. Press anything...";
            getch();
        }
    }
    else
    {
        std::cout << "\n\nInvalid input. Press anything...";
        getch();
    }

    return;
}

void Game::draw()
{
    if (this->activePlayers == 1)
    {
        if (this->stillIn.at(this->currentPlayer[0]))
        {
            if (this->currentPlayer[1] == 1)
            {
                this->players.at(this->currentPlayer[0])->display(false);
            }
            else
            {
                this->players.at(this->currentPlayer[0])->display(true);
            }
            this->events();
        }
        else
        {
            if (this->playersCompleted.at(this->currentPlayer[0]))
            {
                if (this->currentPlayer[1] == 1)
                {
                    std::cout << "Congratulations! You beat solitaire!!";
                    this->gameFinished = true;
                }
            }
            else
            {
                if (this->currentPlayer[1] == 1)
                {
                    std::cout << "Good try, you almost had it!";
                    this->gameFinished = true;
                }
            }
        }
    }
    else
    {
        if (this->moves == 8)
        {
            this->switchPlayer();
        }
        else
        {
            this->players.at(this->currentPlayer[0])->display(true);
            this->events();
        }
    }

    return;
}

void Game::switchPlayer()
{
    system("cls");
    int iterater = 0;
    this->moves = 0;
    do
    {
        iterater++;
        this->currentPlayer[0]++;
        if (this->currentPlayer[0] == this->currentPlayer[1])
        {
            this->currentPlayer[0] = 0;
        }
        if (iterater > this->currentPlayer[1])
        {
            this->endGame = true;
        }
    } while (!(this->stillIn.at(this->currentPlayer[0])) && !(this->endGame));
    if (this->stillIn.at(this->currentPlayer[0]))
    {
        std::cout << "Switching to " << this->players.at(this->currentPlayer[0])->getName() << ". Press anything...";
        getch();
    }

    return;
}

void Game::comparePlayers()
{
    int topScore = this->players.at(0)->getPoints();
    int potentialWinners = 0;
    int lastInPlayer;

    for (int i = 0; i < this->currentPlayer[1]; i++)
    {
        if (this->playersCompleted.at(i))
        {
            lastInPlayer = i;
            potentialWinners++;
        }
    }
    if (potentialWinners == 1)
    {
        std::cout << "Congratulations, " << this->players.at(lastInPlayer)->getName() << "! You won by being the only player to finish the game!";
    }
    else if (potentialWinners > 1)
    {
        for (int i = 0; i < this->currentPlayer[1]; i++)
        {
            if (this->stillIn.at(i))
            {
                if (this->players.at(i)->getPoints() < topScore)
                {
                    topScore = this->players.at(i)->getPoints();
                }
            }
        }
        for (int i = 0; i < this->currentPlayer[1]; i++)
        {
            if (this->stillIn.at(i))
            {
                if (this->players.at(i)->getPoints() == topScore)
                {
                    lastInPlayer = i;
                    potentialWinners++;
                }
                else
                {
                    this->stillIn.at(i) = false;
                }
            }
        }
        if (potentialWinners == 1)
        {
            std::cout << "Congratulations, " << this->players.at(lastInPlayer)->getName() << "! You won by taking less turns!";
        }
        else
        {
            std::cout << "It was a tie between: ";
            for (int i = 0; i < this->currentPlayer[1]; i++)
            {
                if (this->stillIn.at(i))
                {
                    std::cout << "  " << this->players.at(i)->getName() << "   ";
                }
            }
        }
    }
    else
    {
        int foundationSum;

        for (int i = 0; i < this->currentPlayer[1]; i++)
        {
            this->stillIn.at(i) = true;
        }
        potentialWinners = 0;
        topScore = 0;
        for (int i = 0; i < this->currentPlayer[1]; i++)
        {
            if (this->stillIn.at(i))
            {
                foundationSum = this->players.at(i)->getFoundations()[0]->getCards()->size() + this->players.at(i)->getFoundations()[1]->getCards()->size() + this->players.at(i)->getFoundations()[2]->getCards()->size() + this->players.at(i)->getFoundations()[3]->getCards()->size();
                if (foundationSum > topScore)
                {
                    topScore = foundationSum;
                }
            }
        }
        for (int i = 0; i < this->currentPlayer[1]; i++)
        {
            if (this->stillIn.at(i))
            {
                if (this->players.at(i)->getFoundations()[0]->getCards()->size() + this->players.at(i)->getFoundations()[1]->getCards()->size() + this->players.at(i)->getFoundations()[2]->getCards()->size() + this->players.at(i)->getFoundations()[3]->getCards()->size() == topScore)
                {
                    lastInPlayer = i;
                    potentialWinners++;
                }
                else
                {
                    this->stillIn.at(i) = false;
                }
            }
        }
        if (potentialWinners == 1)
        {
            std::cout << "Congratulations, " << this->players.at(lastInPlayer)->getName() << "! You won by having the most cards in your foundations!";
        }
        else
        {
            topScore = this->players.at(0)->getPoints();
            potentialWinners = 0;
            for (int i = 0; i < this->currentPlayer[1]; i++)
            {
                if (this->stillIn.at(i))
                {
                    if (this->players.at(i)->getPoints() < topScore)
                    {
                        topScore = this->players.at(i)->getPoints();
                    }
                }
            }
            for (int i = 0; i < this->currentPlayer[1]; i++)
            {
                if (this->stillIn.at(i))
                {
                    if (this->players.at(i)->getPoints() == topScore)
                    {
                        lastInPlayer = i;
                        potentialWinners++;
                    }
                    else
                    {
                        this->stillIn.at(i) = false;
                    }
                }
            }
            if (potentialWinners == 1)
            {
                std::cout << "Congratulations, " << this->players.at(lastInPlayer)->getName() << "! You won by taking less turns!";
            }
            else
            {
                std::cout << "It was a tie between: ";
                for (int i = 0; i < this->currentPlayer[1]; i++)
                {
                    if (this->stillIn.at(i))
                    {
                        std::cout << "  " << this->players.at(i)->getName() << "   ";
                    }
                }
            }
        }
    }

    return;
}

void Game::help()
{
    system("cls");
    std::cout << "'stock': Puts top card from stock to talon. If stock is empty, recycles it.\n";
    std::cout << "'talon': Accesses the top card of the talon.\n";
    std::cout << "'hearts'/'diamonds'/'clubs'/'spades': Accesses or targets the specified foundation.\n";
    std::cout << "Any combination of valid letter then number: Accesses cards from the specified tableau and row.\n";
    std::cout << "Any valid letter: Targets specified tableau.\n";
    std::cout << "'fail': You give up, and wait for endgame point system.\n";
    std::cout << "'help': Accesses this list of commands\n\n";
    std::cout << "Press anything if you understand the commands...";
    getch();

    return;
}

bool Game::intErrorCatch(std::string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            return false;
        }
    }

    return true;
}

bool Game::validMove(std::string input)
{

}



