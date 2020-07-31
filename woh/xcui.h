#pragma once
#include "cui.h"
#include <fstream>

class ExCUI : public ConsoleUI
{
protected:
    FILE* fp;
public:
    ExCUI();
    virtual ~ExCUI();

	virtual void init_player(vector<string> player);
	virtual void game_start();
	virtual void round_start();
	virtual void wash_cards(vector<Coord> swaps);
	virtual void dispatch_cards(int sit, vector<Card> cards);
	virtual void snd_swap(int sit, vector<Card> cards);
	virtual void rcv_swap(int sit, vector<Card> cards);
	virtual void play_card(int sit, Card c);
	virtual void add_point(int sit, vector<Card> points);
	virtual void update_rnd_score(int* scores);
	virtual void update_score(int* new_score, int* total);
	virtual void round_end();
	virtual void game_end(int* total);
	virtual void force_end(string msg);
};