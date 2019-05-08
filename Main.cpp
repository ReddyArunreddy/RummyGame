#include <iostream>
#include "cards.h"
#include "player.h"
#include "table.h"

#define CARDS_DEALT 13
#define EVEN_ODD 2

bool show;

void PlayGame();
void DealDeck(Player &, Player &, Cards &);
int main(int argc, char *argv[])
{
    std::cout << "Welcome to RummyGame:\n";
    PlayGame();

    return 0;
}

void PlayGame()
{
    std::string name;
    std::cout << "Enter player1 name: ";
    std::getline(std::cin, name);
    Player player1(name);

    std::cout << "Enter player2 name: ";
    std::getline(std::cin, name);
    Player player2(name);

    Cards deck;

    // Initialize the deck and shuffle...
    deck.InitTheDeck();
    deck.ShuffleDeck();

    // Clear the player hand and melded cards...
    player1.ClearHandandMeldedCards();
    player2.ClearHandandMeldedCards();

    DealDeck(player1, player2, deck);
    deck.SetJokerCard();

    unsigned int turn = 0;
    int show_hand;
    while (!show)
    {
        if (turn % EVEN_ODD == 0)
        {
            player1.play(deck);
            std::cout << "Want to show your hand? press 1.\n";
            std::cin >> show_hand;
            if (show_hand == YES)
                player1.SetShowValue(true);
        }
        else
        {
            player2.play(deck);
            std::cout << "Want to show your hand? press 1.\n";
            std::cin >> show_hand;
            if (show_hand == YES)
                player2.SetShowValue(true);
        }
        //std::cin.get();

        ++turn;
    }

    if(player1.GetShowValue())
    {
        player1.Show(deck);
        player2.CalculateHandScore(deck);
        player1.SetShowValue(false);
    }

    if(player2.GetShowValue())
    {
        player2.Show(deck);
        player1.CalculateHandScore(deck);
        player2.SetShowValue(false);
    }
}

void DealDeck(Player &player1, Player &player2, Cards &deck)
{
    int i = 0;
    while (i < EVEN_ODD * CARDS_DEALT)
    {
        player1.InsertCardIntoHand(deck.TopCardOfClosedDeck());
        deck.PopCardFromClosedDeck();
        i++;
        player2.InsertCardIntoHand(deck.TopCardOfClosedDeck());
        deck.PopCardFromClosedDeck();
        i++;
    }
    deck.AddCardToOpenDeck();
    deck.SetJokerCard();
}