#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include "cards.h"
#include "table.h"
#define PICK_FROM_DECK -1
#define YES 1
#define END -1
#define RANK_OFFSET 2
#define TWO_THROUGH_NINE_PTS 5
#define TEN_THROUGH_KING_PTS 10
#define ACE_POINTS 15
#define JOKER_POINTS 0
#define EMPTY 0
#define NUMBER_TO_CHECK 2
#define NEXT 1
#define NEXT_NEXT 2
#define PICK_FROM_OPEN_DECK 1
#define PICK_FROM_CLOSED_DECK 2
#define FALSE_SHOW 100
class Table;
class Cards;
class Player
{
private:
    std::string m_PlayerName;               // Player name
    int m_PlaterScore;                      // Player score
    std::vector<std::string> m_MeldedCards; // All melded cards will be held here
    std::vector<std::string> m_PlayerHand;  // All 13 cards will be held here

    std::vector<std::string> m_PureSequence;
    std::vector<std::string> m_ValidSequence;
    std::vector<std::string> m_Set1;
    std::vector<std::string> m_Set2;
    std::vector<std::string> m_TempMeldCards;
    bool m_IsPureSequence;
    bool m_IsValidSequence;
    bool m_Show;
    int m_TableNo;

public:
    //static bool show;
    //Player class constructor.
    Player(std::string name, int score = 0);

    // Returns the player name.
    std::string GetName() const;

    //Returns the player score.
    int GetScore() const;

    // Returns the player hand size.
    int GetHandsize() const;

    // Calculates the player score.
    int CalculateHandScore(Cards &);

    // Clears the both Player's hand and Melded hand.
    void ClearHandandMeldedCards();

    // Returns the Card value.
    std::string GetHandValue(const int &number) const;

    // Inserts the card into player hand.
    void InsertCardIntoHand(const std::string &card);

    // Discards the card from the player hand.
    void DiscardCardFromHand(const int &number);

    // Display's the cards in players hand.
    void DisplayHand() const;

    // Displays the melded cards of the player.
    void DisplayMeldedCards() const;

    // Organizes the cards in the player hand's
    void OrganizeHand();

    //
    int WhatDeckToPickFrom(const Cards &);

    void JoinTable(Table table);

    int LeaveTable();

    void play(Cards &deck);

    void MeldTheCards(const std::vector<int> &, Cards &);

    std::vector<int> CardsToMeld();

    void DiscardCard(Cards &, const int &);

    int WhatCardToDiscard() const;

    void EraseTheMeldCardFromHand(std::vector<int>);

    void Show(Cards &);

    void ValidateShow();

    void FindCardSequenceOrSet(Cards &);

    bool IsAPureSequence(std::vector<int> &, std::vector<char> &);

    bool ISAValidSequence(std::vector<int> &, std::vector<char> &, Cards &);

    bool IsASet(std::vector<int> &, std::vector<char> &, Cards &);

    bool IsSuitAvailable(const std::vector<char> &, const char &) const;

    int PreviousCard(int &card_number) const;

    void SetShowValue(bool);

    bool GetShowValue() const;
};

//bool Player::show = 0;

#endif