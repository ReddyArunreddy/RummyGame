#include "player.h"
extern bool show;

Player::Player(std::string name, int score)
{
	m_PlayerName = name;
	m_PlaterScore = score;
}
void Player::ClearHandandMeldedCards()
{
	m_MeldedCards.clear();
	m_PlayerHand.clear();
}

int Player::GetHandsize() const
{
	return m_PlayerHand.size();
}
void Player::JoinTable(Table table)
{
	m_TableNo = table.m_TableNo;
	table.AddPlayerToTable();
}

int Player::WhatCardToDiscard() const
{
	int card_to_discard;
	std::cout << "Please chose the card to discard.\n";
	std::cin >> card_to_discard;

	while (card_to_discard < EMPTY || card_to_discard >= GetHandsize())
	{
		std::cout << "Please the right card index.\n";
		std::cin >> card_to_discard;
	}

	return card_to_discard;
}

void Player::InsertCardIntoHand(const std::string &card)
{
	m_PlayerHand.push_back(card);
}

void Player::play(Cards &deck)
{
	std::cout << "Your turn " << GetName() << "\n";
	deck.ShowOpenDeckCards();
	deck.ShowJokerCard();
	OrganizeHand();
	DisplayHand();

	int choice = WhatDeckToPickFrom(deck);
	if (choice != PICK_FROM_CLOSED_DECK)
	{
		InsertCardIntoHand(deck.PickFromOpenDeck());
		OrganizeHand();
		DisplayHand();
		MeldTheCards(CardsToMeld(), deck);
		DisplayMeldedCards();
	}
	else
	{
		InsertCardIntoHand(deck.PickFromClosedDeck());
		OrganizeHand();
		DisplayHand();
		MeldTheCards(CardsToMeld(), deck);
		DisplayMeldedCards();
	}

	if (GetHandsize() > EMPTY)
	{
		OrganizeHand();
		DisplayHand();
		DiscardCard(deck, WhatCardToDiscard());
	}

	std::cout << "\n\n";
}

void Player::DiscardCard(Cards &deck, const int &card_spot)
{
	std::string card_to_discard = m_PlayerHand[card_spot];
	deck.InsertIntoOpenDeckFromHand(card_to_discard);
	m_PlayerHand.erase(m_PlayerHand.begin() + card_spot);
}

void Player::DisplayMeldedCards() const
{
	std::cout << "\nYour melded cards are:\n";
	for (unsigned int i = 0; i < m_MeldedCards.size(); i++)
	{
		std::cout << m_MeldedCards[i] << " ";
	}
	std::cout << "\n\n";
}

std::vector<int> Player::CardsToMeld()
{
	std::vector<int> card_to_meld;
	int card_location = EMPTY;

	std::cout << "\nWhich cards do you want to meld from your hand.\n";
	std::cout << " Chose three or four card.\n";
	std::cout << "Pres -1 to end.\n\n";
	while (card_location != END)
	{
		std::cin >> card_location;
		if (card_location != END)
			card_to_meld.push_back(card_location);
	}

	return card_to_meld;
}

void Player::MeldTheCards(const std::vector<int> &cards_pos_to_meld, Cards &deck)
{
	if(!cards_pos_to_meld.size())
		return;
	for (unsigned int i = 0; i < cards_pos_to_meld.size(); i++)
	{
		int card_spot = cards_pos_to_meld[i];
		std::string card = m_PlayerHand[card_spot];
		m_MeldedCards.push_back(card);
		m_TempMeldCards.push_back(card);
	}
	//remove the card from hand...
	EraseTheMeldCardFromHand(cards_pos_to_meld);
	// sort meld cards...
	std::sort(m_MeldedCards.begin(), m_MeldedCards.end());
	std::cout << "calling FindCardSequenceOrSet.\n";
	FindCardSequenceOrSet(deck);
}

void Player::EraseTheMeldCardFromHand(std::vector<int> cards_to_delete)
{
	for (int j = 1; j < cards_to_delete.size(); j++)
	{
		cards_to_delete[j] = cards_to_delete[j] - j;
	}
	for (unsigned int i = 0; i < cards_to_delete.size(); i++)
	{
		int card_spot = cards_to_delete[i];
		m_PlayerHand.erase(m_PlayerHand.begin() + card_spot);
	}
}

int Player::WhatDeckToPickFrom(const Cards &deck)
{
	int choice;
	std::cout << "\n1. Pick from open deck(pick up pile).\n"
			  << "2. Pick from closed deck.\n\n";
	std::cin >> choice;
	if (choice == PICK_FROM_OPEN_DECK)
	{
		return PICK_FROM_OPEN_DECK;
	}
	else
	{
		return PICK_FROM_CLOSED_DECK;
	}
}
std::string Player::GetName() const
{
	return m_PlayerName;
}

void Player::OrganizeHand()
{
	std::sort(m_PlayerHand.begin(), m_PlayerHand.end());
}

void Player::DisplayHand() const
{
	std::cout << "Your hand " << GetName() << " \n";
	for (unsigned int i = 0; i < m_PlayerHand.size(); i++)
	{
		std::cout << m_PlayerHand[i] << " ";
	}
	std::cout << "\n\n";
}

void Player::Show()
{
	DisplayMeldedCards();
	show = true;
}

void Player::FindCardSequenceOrSet(Cards &deck)
{
	std::vector<int> numbers;
	std::vector<char> suits;
	std::cout << "in FindCardSequenceOrSet.\n";
	for (unsigned short i = 0; i < m_TempMeldCards.size(); i++)
	{
		std::string number = m_TempMeldCards[i].substr(0, m_TempMeldCards[i].find("-"));
		int num = std::atoi(number.c_str());
		char sui = m_TempMeldCards[i].substr(m_TempMeldCards[i].find("-") + 1).at(0);
		numbers.push_back(num);
		suits.push_back(sui);
	}
	std::cout << "after for loop.\n";
	if (IsAPureSequence(numbers, suits))
	{
		std::cout << "It's pure sequence.\n";
		m_PureSequence = m_TempMeldCards;
	}
	else if (ISAValidSequence(numbers, suits, deck))
	{
		std::cout << "It's a valid sequence.\n";
		m_ValidSequence = m_TempMeldCards;
	}
	else if(IsASet(numbers, suits, deck))
	{
		std::cout << "It's a set.\n";
	}
}

bool Player::IsAPureSequence(std::vector<int> &numbers, std::vector<char> &suits)
{
	/*
	bool istrue3;
	bool istrue4;
	int i = 0;
	if (numbers[i] == numbers[i + 1] - 1 &&
		numbers[i + 1] == numbers[i + 2] - 1)
	{
		if (numbers.size() == 4)
			if (numbers[i + 2] == numbers[i + 3] - 1)
				istrue4 = true;

		istrue3 = true;
	}

	i = 0;
	if (istrue3)
	{
		if (suits[i] == suits[i + 1] == suits[i + 2])
			return true;
	}

	i = 0;
	if (istrue4)
	{
		if (suits[i] == suits[i + 1] == suits[i + 2] == suits[i + 3])
			return true;
	}
	*/

	bool is_pure_sequence;
	std::cout << "In IsAPureSequence\n";
	//for sequence A(14) 2 3 or A(14) 2 3 4...
	if (numbers[0] = 14)
	{
		for (unsigned int i = 2; i < numbers.size(); i++)
		{
			if (numbers[i] == numbers[i - 1] + 1 && suits[i] == suits[i - 1])
				is_pure_sequence = true;
			else
			{
				is_pure_sequence = false;
				break;
			}
		}
		if (is_pure_sequence)
			return true;
	}

	for (int i = 1; i < numbers.size(); i++)
	{
		if (numbers[i] == numbers[i - 1] + 1 && suits[i] == suits[i - 1])
			is_pure_sequence = true;
		else
		{
			is_pure_sequence = false;
			break;
		}
	}

	if (is_pure_sequence)
		return true;
	return false;
}

bool Player::ISAValidSequence(std::vector<int> &numbers, std::vector<char> &suits, Cards &deck)
{
	int J_Joker = 0; //Joker present in the card...
	int O_Joker = 0; // Open joker...
	bool is_joker = false;
	std::vector<int> cardnumber;
	std::vector<char> cardsuit;
	std::vector<int> jokerindex;
	bool is_valid_sequence = false;
	std::string number = deck.ReturnJoker().substr(0, deck.ReturnJoker().find("-"));
	int jokernumber = std::atoi(number.c_str());
	// find out how many joker cards are present...
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] == std::atoi(JOKER))
		{
			++J_Joker;
			is_joker = true;
		}
		if (numbers[i] == jokernumber &&
			suits[i] == deck.ReturnJoker().substr(deck.ReturnJoker().find("-") + 1).at(0))
		{
			++O_Joker;
			is_joker = true;
		}
		if (!is_joker)
		{
			
		}
		else
		{
			cardnumber.push_back(numbers[i]);
			cardsuit.push_back(suits[i]);
		}
		

		is_joker = false;
	}
	if (cardnumber.size() == 1) // as there will be only card left as remaining are jokers...
		return true;

	// check the cards form a valid sequence or not...
	for (int i = 1; i < cardnumber.size(); i++)
	{
		if ((cardnumber[i] == cardnumber[i - 1] + 1) && cardsuit[i] == cardsuit[i - 1])
			is_valid_sequence = true;
		else
			is_valid_sequence = false;
		if (i == 1 && is_valid_sequence == false)
			break;
	}
	if (is_valid_sequence)
		return true;
	return false;
}

bool Player::IsASet(std::vector<int> &numbers, std::vector<char> &suits, Cards &deck)
{
	bool is_a_set = false;

	int J_Joker = 0; //Joker present in the card...
	int O_Joker = 0; // Open joker...
	bool is_joker = false;
	std::vector<int> cardnumber;
	std::vector<char> cardsuit;
	std::string number = deck.ReturnJoker().substr(0, deck.ReturnJoker().find("-"));
	int jokernumber = std::atoi(number.c_str());
	// find out how many joker cards are present...
	std::cout << "In IsASet\n";
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] == std::atoi(JOKER))
		{
			++J_Joker;
			is_joker = true;
		}
		if (numbers[i] == jokernumber &&
			'J' == deck.ReturnJoker().substr(deck.ReturnJoker().find("-") + 1).at(0))
		{
			++O_Joker;
			is_joker = true;
		}
		if (!is_joker)
		{
			cardnumber.push_back(numbers[i]);
			cardsuit.push_back(suits[i]);
		}

		is_joker = false;
	}

	for (unsigned int i = 1; i < cardnumber.size(); i++)
	{
		if (cardnumber[i] == cardnumber[i - 1] && !IsSuitAvailable(cardsuit, cardsuit[i - 1]))
			is_a_set = true;
		else
		{
			is_a_set = false;
			break;
		}
	}
	std::cout << "In IsASet\n";
	if (is_a_set && ((cardnumber.size() + O_Joker + J_Joker) == numbers.size()))
		return true;
	std::cout << "In IsASet\n";
	return false;
}

/*

*/
bool Player::IsSuitAvailable(const std::vector<char> &suits, const char &suit) const
{
	int cnt = 0;
	for (unsigned int i = 0; i < suits.size(); i++)
	{
		if (suit == suits[i])
			++cnt;
	}

	if (cnt >= 2)
		return true;
	return false;
}