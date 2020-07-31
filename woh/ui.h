#pragma once
#include "defs.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class GameUI
{
public:
	virtual ~GameUI();

	virtual void init_player(vector<string> player) = 0;
	virtual void game_start() = 0;
	virtual void round_start() = 0;
	virtual void wash_cards(vector<Coord> swaps) = 0;
	virtual void dispatch_cards(int sit, vector<Card> cards) = 0;
	virtual void snd_swap(int sit, vector<Card> cards) = 0;
	virtual void rcv_swap(int sit, vector<Card> cards) = 0;
	virtual void play_card(int sit, Card c) = 0;
	virtual void add_point(int sit, vector<Card> points) = 0;
	virtual void update_rnd_score(int* scores) = 0;
	virtual void update_score(int* new_score, int* total) = 0;
	virtual void round_end() = 0;
	virtual void game_end(int* total) = 0;
	virtual void force_end(string msg) = 0;
};