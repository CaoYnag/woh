#pragma once
#include "defs.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class Player
{
public:
	virtual ~Player();

	virtual void sit(int s) = 0;
	// when a game start, set init cards for player
	virtual void set_cards(vector<Card> cards) = 0;
	// player need to select 3 cards to swap with another player
	virtual vector<Card> swap(int num) = 0;
	// rcv 3 cards from player who swapping cards with
	virtual void rcv_swap(const vector<Card>& cards) = 0;
	// play a card in a round
	virtual Card play_card(const vector<Card>& deck) = 0;
	virtual void circle_end(int sit, const vector<Card>& cards) = 0;

	// player name
	virtual string name() const = 0;
};