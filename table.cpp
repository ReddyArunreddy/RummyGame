#include "table.h"

Table::Table()
{
    //Table::m_TableNo++;
    m_NoOfPlayers = 0;
}

bool Table::isTableFull()
{
    return m_NoOfPlayers >= 6;
}

void Table::AddPlayerToTable()
{
    ++m_NoOfPlayers;
}

void Table::DealDeck()
{
}