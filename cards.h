//#pragma once
#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

#define DECK_SIZE 54
#define CARDS_PER_PLAYER 13
#define NUMBER_OF_RANKS 13
#define NUMBER_OF_SUITS 4
#define NUMBER_OF_JOKERS 2
#define RANK_OFFSET 2
#define ONE 1
#define TEN "10"
#define JACK "11"
#define QUEEN "12"
#define KING "13"
#define ACE "14"
#define JOKER "15"
#define DIAMOND "-D"
#define SPADE "-S"
#define CLUB "-C"
#define HEART "-H"
#define JOKERS "-J"

enum Rank
{
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

enum Suit
{
	D,
	H,
	S,
	C
};

class Cards
{
private:
	std::vector<std::string> m_OpenDeck;
	std::vector<std::string> m_ClosedDeck;
	std::string m_Joker;

public:
	void InitTheDeck();
	void ShuffleDeck();
	int DeckSize() const;
	std::string PickFromOpenDeck();
	std::string PickFromClosedDeck();
	void DiscardCardFromHand();
	std::string TopCardOfClosedDeck();
	void PopCardFromClosedDeck();
	void ShowOpenDeckCards() const;
	void SetJokerCard();
	int GetOpenDeckSize() const;
	void AddCardToOpenDeck();
	void InsertIntoOpenDeckFromHand(std::string &card);
	void ShowJokerCard();
	std::string ReturnJoker();
};

#endif