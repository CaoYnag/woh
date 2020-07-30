#pragma once
#include <game.h>
#include <vector>
#include <list>
#include <map>
using namespace std;

class MinMon : public Player
{
protected:
	bool _can_play_point;
	list<Card> _hands;
	bool exist(Card c);
	void sort();

	void log(const string& msg);
	void log_hands();
	void log(const Card& c);
public:
	MinMon();
	virtual ~MinMon();

	virtual void sit(int s);
	virtual void set_cards(vector<Card> cards);
	virtual vector<Card> swap(int num);
	virtual void rcv_swap(const vector<Card>& cards);
	virtual Card play_card(const vector<Card>& deck);
	virtual void circle_end(int sit, const vector<Card>& cards);

	virtual string name() const;
};

