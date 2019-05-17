#include "player.h"
extern bool is_genuine_show;

Player::Player(std::string name, int score)
{
	m_PlayerName = name;
	m_PlayerScore = score;
	m_IsPureSequence = false;
	m_IsValidSequence = false;
	m_IsValidSet = false;
}
void Player::ClearHandandMeldedCards()
{
	m_MeldedHand.clear();
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
	/*
	std::cin >> card_to_discard;

	while (card_to_discard < EMPTY || card_to_discard >= GetHandsize())
	{
		std::cout << "Please the right card index.\n";
		std::cin >> card_to_discard;
	}
	*/
	std::string card;
	std::cin >> card;
	bool card_present = false;
	while(!card_present)
	{
		auto it = std::find(m_PlayerHand.begin(), m_PlayerHand.end(), card);
		if(it != m_PlayerHand.end())
		{
			card_to_discard = std::distance(m_PlayerHand.begin(), it);
			card_present = true;
		}
		else
		{
			std::cout << "Enterd card is not present !!\n";
			std::cout << "Please enter thye correct card\n";
		}
		
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
	DisplayMeldedCards();
	//OrganizeHand();
	DisplayHand();

	int choice = WhatDeckToPickFrom(deck);
	if (choice != PICK_FROM_CLOSED_DECK)
	{
		InsertCardIntoHand(deck.PickFromOpenDeck());
		//OrganizeHand();
		DisplayHand();
		MeldTheCards(CardsToMeld(), deck);
		DisplayMeldedCards();
	}
	else
	{
		InsertCardIntoHand(deck.PickFromClosedDeck());
		//OrganizeHand();
		DisplayHand();
		MeldTheCards(CardsToMeld(), deck);
		DisplayMeldedCards();
	}

	if (GetHandsize() > EMPTY)
	{
		//OrganizeHand();
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
	std::cout << "Pure Sequence: ";
	for(int i=0; i<m_PureSequence.size(); i++)
		std::cout << m_PureSequence[i] << " ";
	std::cout << "\n";

	std::cout << "Valid Sequence: ";
	for(int i=0; i<m_ValidSequence.size(); i++)
		std::cout << m_ValidSequence[i] << " ";
	std::cout << "\n";

	std::cout << "Set1: ";
	for(int i=0; i<m_Set1.size(); i++)
		std::cout << m_Set1[i] << " ";
	std::cout << "\n";

	std::cout << "Set2: ";
	for(int i=0; i<m_Set2.size(); i++)
		std::cout << m_Set2[i] << " ";
	std::cout << "\n\n\n";
}

std::vector<int> Player::CardsToMeld()
{
	std::vector<int> card_to_meld;
	int card_location = EMPTY;

	std::cout << "\nWhich cards do you want to meld from your hand.\n";
	std::cout << "Chose three or more cards.\n";
	
	std::string card;
	std::cout << "Pres 0 to end.\n\n";
	m_TempMeldCards.clear();
	while(card != "0")
	{
		std::cin >> card;
		auto it = std::find(m_PlayerHand.begin(), m_PlayerHand.end(), card);
		if(it != m_PlayerHand.end())
		{
			int index = std::distance(m_PlayerHand.begin() , it);
			card_to_meld.push_back(index);
			m_MeldedHand.push_back(card);
			m_TempMeldCards.push_back(card);
		}
		else if(card != "0")
		{
			std::cout << "Enter card is not present!! Please enter the right card.\n";
		}
	}
	
	if(card_to_meld.size() < 3)
		card_to_meld.clear();
	
	return card_to_meld;

	
}

void Player::MeldTheCards(const std::vector<int> &cards_pos_to_meld, Cards &deck)
{
	if (!cards_pos_to_meld.size())
		return;

	FindCardSequenceOrSet(deck);
	if(m_PureSequence.size() || m_ValidSequence.size() || m_Set1.size() || m_Set2.size())
	{
		//remove the card from hand...
		EraseTheMeldCardFromHand(cards_pos_to_meld);
	}
	else
	{
		std::cout << "The chosen cards doesn't form any sequence or set:\n";
		std::cout << "Please chose the correct cards next time.\n";
	}
}

void Player::EraseTheMeldCardFromHand(std::vector<int> cards_to_delete)
{
	std::sort(cards_to_delete.begin(), cards_to_delete.end());
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

int Player::GetScore() const
{
	return m_PlayerScore;
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

void Player::Show(Cards &deck)
{
	if(m_IsPureSequence && m_IsValidSequence)
	{
		std::cout << "It's valid show.\n";
		is_genuine_show = true;
	}	
	else
	{
		std::cout << "It's not valid show.\n";
		std::cout << "You hand don't have a Pure sequence and a Valid sequence.\n";
		m_PlayerScore = FALSE_SHOW;
		std::cout << GetName() << " Your score is: " << GetScore() << "\n";
		is_genuine_show = false;
		return;
	}

	std::cout << GetName() << " Your score is: " << CalculateHandScore(deck) << "\n";
}

void Player::FindCardSequenceOrSet(Cards &deck)
{
	std::vector<int> numbers;
	std::vector<char> suits;
	for (unsigned short i = 0; i < m_TempMeldCards.size(); i++)
	{
		std::string number = m_TempMeldCards[i].substr(0, m_TempMeldCards[i].find("-"));
		int num = std::atoi(number.c_str());
		char sui = m_TempMeldCards[i].substr(m_TempMeldCards[i].find("-") + 1).at(0);
		numbers.push_back(num);
		suits.push_back(sui);
	}
	if (IsAPureSequence(numbers, suits))
	{
		std::cout << "It's pure sequence.\n";
		m_PureSequence = m_TempMeldCards;
		m_IsPureSequence = true;
	}
	else if (ISAValidSequence(numbers, suits, deck))
	{
		std::cout << "It's a valid sequence.\n";
		m_ValidSequence = m_TempMeldCards;
		m_IsValidSequence = true;
	}
	else if (IsASet(numbers, suits, deck))
	{
		std::cout << "It's a set.\n";
		if(!m_Set1.size())
			m_Set1 = m_TempMeldCards;
		else
			m_Set2 = m_TempMeldCards;

		m_IsValidSet = true;
	}
}

bool Player::IsAPureSequence(std::vector<int> &numbers, std::vector<char> &suits)
{
	bool is_pure_sequence;
	//for sequence A(14) 2 3 or A(14) 2 3 4...
	if (numbers[0] == 14)
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
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		cardnumber.push_back(numbers[i]);
		cardsuit.push_back(suits[i]);
	}
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] == std::atoi(JOKER))
		{
			++J_Joker;
			is_joker = true;
		}
		if (numbers[i] == jokernumber)
		{
			++O_Joker;
			is_joker = true;
		}
		if (is_joker)
		{
			if (i == 0)
			{
				cardnumber[0] = PreviousCard(cardnumber[1]);
				cardsuit[0] = cardsuit[1];
			}
			if (i == numbers.size() - 1)
			{
				cardnumber[i] = cardnumber[i - 1] + 1;
				cardsuit[i] = cardsuit[i - 1];
			}
			else
			{
				cardnumber[i] = PreviousCard(cardnumber[i + 1]);
				cardsuit[i] = cardsuit[i + 1];
			}
		}
		is_joker = false;
	}

	if (IsAPureSequence(cardnumber, cardsuit))
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
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] == std::atoi(JOKER))
		{
			++J_Joker;
			is_joker = true;
		}
		if (numbers[i] == jokernumber)
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
		if ((cardnumber[i] == cardnumber[i - 1]) && (!IsSuitAvailable(cardsuit, cardsuit[i - 1])))
		{
			is_a_set = true;
		}
		else
		{
			is_a_set = false;
			break;
		}
	}

	if (is_a_set && (cardnumber.size() + O_Joker + J_Joker == numbers.size()))
		return true;

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

int Player::PreviousCard(int &card_number) const
{
	switch (card_number)
	{
	case 2:
		return 14;
	case 3:
		return 2;
	case 4:
		return 3;
	case 5:
		return 4;
	case 6:
		return 5;
	case 7:
		return 6;
	case 8:
		return 7;
	case 9:
		return 8;
	case 10:
		return 9;
	case 11:
		return 10;
	case 12:
		return 11;
	case 13:
		return 12;
	case 14:
		return 13;
	}
}

int Player::CalculateHandScore(Cards &deck)
{
	if(m_IsPureSequence && m_IsValidSequence)
		return CalculatePlayerHandScore(deck);
	else
		return CalculateMeldedHandScore(deck) + CalculatePlayerHandScore(deck);
}
int Player::CalculateMeldedHandScore(Cards &deck)
{
	int score = 0;
	std::vector<int> temp;
	std::string number = deck.ReturnJoker().substr(0, deck.ReturnJoker().find("-"));
	int jokernumber = std::atoi(number.c_str());
	for(unsigned int i=0; i< m_MeldedHand.size(); i++)
	{
		std::string number = m_MeldedHand[i].substr(0, m_MeldedHand[i].find("-"));
		int num = std::atoi(number.c_str());
		if(num != jokernumber)
			temp.push_back(num);
	
	}
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if(temp[i] != 15)
		{
			score += temp[i];
		}
	}

	return score;
}

int Player::CalculatePlayerHandScore(Cards &deck)
{
	int score = 0;
	std::vector<int> temp;
	std::string number = deck.ReturnJoker().substr(0, deck.ReturnJoker().find("-"));
	int jokernumber = std::atoi(number.c_str());
	for(unsigned int i=0; i< m_PlayerHand.size(); i++)
	{
		std::string number = m_PlayerHand[i].substr(0, m_PlayerHand[i].find("-"));
		int num = std::atoi(number.c_str());
		if(num != jokernumber)
			temp.push_back(num);		
	}
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if(temp[i] != 15)
		{
			score += temp[i];
		}
	}	

	return score;
}

void Player::SetShowValue(bool val)
{
	m_Show = val;
}

bool Player::GetShowValue() const
{
	return m_Show;
}

bool Player::ValidatePlayerMeldedHand()
{
	if(m_IsPureSequence && m_IsValidSequence)
		return true;
	
	return false;
}
bool compare(std::string card1, std::string card2)
{
	std::string number1 = card1.substr(0, card1.find("-"));
	int first = std::atoi(number1.c_str());	
	std::string number2 = card2.substr(0, card2.find("-"));
	int second = std::atoi(number2.c_str());
	std::cout << "sort\n";
	return first < second;	
}

void Player::InitialHandSort()
{
	std::vector<std::string> Club;
	std::vector<std::string> Diamond;
	std::vector<std::string> Heart;
	std::vector<std::string> Spade;
	std::vector<std::string> Joker;
	//std::sort(m_PlayerHand.begin(), m_PlayerHand.end());
	for(int i=0; i<m_PlayerHand.size(); i++)
	{
		std::cout << "In Initialsort\n";
		char suit = m_PlayerHand[i].substr(m_PlayerHand[i].find("-") + 1).at(0);
		if(suit == 'C')
		{
			Club.push_back(m_PlayerHand[i]);
		}
		else if (suit == 'D')
		{
			Diamond.push_back(m_PlayerHand[i]);
		}
		else if (suit == 'H')
		{
			Heart.push_back(m_PlayerHand[i]);
		}
		else if (suit == 'S')
		{
			Spade.push_back(m_PlayerHand[i]);
		}
		else
		{
			Joker.push_back(m_PlayerHand[i]);
		}
	}
	for (int i = 0; i < Club.size(); i++)
	{
		std::cout << Club[i] << " ";
	}
	std::cout <<"\n";
	std::sort(Club.begin(), Club.end(), compare);
	std::sort(Diamond.begin(), Diamond.end(), compare);
	std::sort(Heart.begin(), Heart.end(), compare);
	std::sort(Spade.begin(), Spade.end(), compare);
	m_PlayerHand.clear();
	std::cout << "player hand:\n";
	for (int i = 0; i < m_PlayerHand.size(); i++)
	{
		
		std::cout << m_PlayerHand[i] << " ";
	}
	for (int i = 0; i < Club.size(); i++)
	{
		m_PlayerHand.push_back(Club[i]);
	}
	for (int i = 0; i < Diamond.size(); i++)
	{
		m_PlayerHand.push_back(Diamond[i]);
	}
	for (int i = 0; i < Heart.size(); i++)
	{
		m_PlayerHand.push_back(Heart[i]);
	}
	for (int i = 0; i < Spade.size(); i++)
	{
		m_PlayerHand.push_back(Spade[i]);
	}
	for (int i = 0; i < Joker.size(); i++)
	{
		m_PlayerHand.push_back(Joker[i]);
	}
	

}