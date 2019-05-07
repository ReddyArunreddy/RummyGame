#include "cards.h"

void Cards::InitTheDeck()
{
	for (int r = 0; r < NUMBER_OF_RANKS; r++)
	{
		for (int s = 0; s < NUMBER_OF_SUITS; s++)
		{
			std::string card;
			Rank cardRank = Rank(r);
			switch (cardRank)
			{
			case (Two):
			case (Three):
			case (Four):
			case (Five):
			case (Six):
			case (Seven):
			case (Eight):
			case (Nine):
				card += cardRank + RANK_OFFSET + '0';
				break;
			case (Ten):
				card = TEN;
				break;
			case (Jack):
				card = JACK;
				break;
			case (Queen):
				card = QUEEN;
				break;
			case (King):
				card = KING;
				break;
			case (Ace):
				card = ACE;
			}

			Suit cardSuit = Suit(s);
			switch (cardSuit)
			{
			case (D):
				card.append(DIAMOND);
				break;
			case (H):
				card.append(HEART);
				break;
			case (S):
				card.append(SPADE);
				break;
			case (C):
				card.append(CLUB);
			}

			m_ClosedDeck.push_back(card);
		}
	}
	std::string card = JOKER;
	card.append(JOKERS);
	m_ClosedDeck.push_back(card);
	m_ClosedDeck.push_back(card);
}

void Cards::ShuffleDeck()
{
	std::random_device rd;
	std::mt19937 Generator(rd());
	std::shuffle(m_ClosedDeck.begin(), m_ClosedDeck.end(), Generator);
}

void Cards::PopCardFromClosedDeck()
{
	m_ClosedDeck.pop_back();
}

std::string Cards::TopCardOfClosedDeck()
{
	return m_ClosedDeck[DeckSize() - ONE];
}

int Cards::DeckSize() const
{
	return m_ClosedDeck.size();
}

void Cards::ShowOpenDeckCards() const
{
	if (!m_OpenDeck.size())
	{
		std::cout << "\nCurrently there are no cards in open deck(pick up pile):\n";
		return;
	}
	std::cout << "\nOpen deck cards.\n";
	for (unsigned int i = 0; i < m_OpenDeck.size(); i++)
	{
		std::cout << m_OpenDeck[i] << " ";
	}
	std::cout << "\n";
}

int Cards::GetOpenDeckSize() const
{
	return m_OpenDeck.size();
}

std::string Cards::PickFromOpenDeck()
{
	std::string current_open_card = m_OpenDeck[m_OpenDeck.size() - 1];
	m_OpenDeck.pop_back();
	return current_open_card;
}

std::string Cards::PickFromClosedDeck()
{
	std::string current_closed_deck_card = m_ClosedDeck[m_ClosedDeck.size() - 1];
	m_ClosedDeck.pop_back();
	std::cout << "The card picked from the closed deck is " << current_closed_deck_card << ".\n";
	return current_closed_deck_card;
}

void Cards::AddCardToOpenDeck()
{
	std::string card = m_ClosedDeck[m_ClosedDeck.size() - 1];
	m_ClosedDeck.pop_back();
	m_OpenDeck.push_back(card);
}
void Cards::SetJokerCard()
{
	std::string card = m_ClosedDeck[m_ClosedDeck.size() - 1];
	m_ClosedDeck.pop_back();
	m_Joker = card;
}

void Cards::ShowJokerCard()
{
	std::cout << "\nOpen Joker " << m_Joker << "\n\n";
}

void Cards::InsertIntoOpenDeckFromHand(std::string &card_to_discard)
{
	m_OpenDeck.push_back(card_to_discard);
}
std::string Cards::ReturnJoker()
{
	return m_Joker;
}