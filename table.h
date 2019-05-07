//#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "cards.h"
#define NO_OF_PLAYERS_PER_TABLE 6

class Cards;
class Player;

class Table
{
public:
    int m_TableNo;

private:
    int m_NoOfPlayers;

public:
    Table();
    int GetTableCount();
    bool isTableFull();
    void AddPlayerToTable();
    void DealDeck();
};

//int Table::m_TableNo;

#endif