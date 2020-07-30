#include "MinMon.h"
#include <algorithm>
#include <iostream>
using namespace std;

MinMon::MinMon()
{
}


MinMon::~MinMon()
{
}


void MinMon::log(const string& msg)
{
	//cout << "[" << _name << "] " << msg << endl;
}

void MinMon::log_hands()
{
	string str;
	char buff[2048];
	str += itoa(_hands.size(), buff, 10);
	str += ": ";
	for(auto it = _hands.begin(); it != _hands.end(); ++it)
		str += " " + card_str(*it);
	log(str);
}

void MinMon::log(const Card& c)
{
	string str = " play " + card_str(c);
	log(str);
}

void MinMon::sit(int s)
{
}

bool MinMon::exist(Card c)
{
	return find(_hands.begin(), _hands.end(), c) != _hands.end();
}

void MinMon::sort()
{
	_hands.sort();
}

void MinMon::set_cards(vector<Card> cards)
{
	_hands.clear();
	_hands.assign(cards.begin(), cards.end());
	sort();
	_can_play_point = false;
}

vector<Card> MinMon::swap(int num)
{
	vector<Card> to_swap;
	for(int i = 0; i < num; ++i)
	{
		to_swap.push_back(_hands.back());
		_hands.pop_back();
	}
	return to_swap;		
}

void MinMon::rcv_swap(const vector<Card>& cards)
{
	for(auto it = cards.begin(); it != cards.end(); ++it)
		_hands.push_back(*it);
	sort();
}

Card MinMon::play_card(const vector<Card>& deck)
{
	log_hands();
	Card ret;
	if(deck.size() == 0 && exist(Card(Club, N2)))
	{
		ret = Card(Club, N2);
		_hands.remove(ret);
	} 
	else if(deck.size() == 0)
	{
		ret = _hands.front();
		int cnt = 0;
		while(is_point_card(ret) && !_can_play_point)
		{
			_hands.pop_front();
			_hands.push_back(ret);
			ret = _hands.front();
			if(++cnt == _hands.size())
				break;
		}
		_hands.pop_front();
	}
	else
	{

		u8 c = deck[0].c;
		for(auto it = _hands.begin(); it != _hands.end(); ++it)
		{
			if((*it).c == c)
			{
				ret = *it;
				_hands.remove(*it);
				break;
			}
		}
		if(ret.c == CUnset) // not find same color
		{
			ret = _hands.front();
			int cnt = 0;
			while(_hands.size() == Game::FULL_HANDS_CARD_NUM && ret.c == Heart)
			{
				_hands.pop_front();
				_hands.push_back(ret);
				ret = _hands.front();
				if(++cnt == _hands.size())
					break;
			}
			_hands.pop_front();
		}
	}
	sort();
	log(ret);
	return ret;
}

void MinMon::circle_end(int sit, const vector<Card>& cards)
{
	if(!_can_play_point) for(int i = 0; i < cards.size(); ++i)
		if(is_point_card(cards[i]))
		{
			_can_play_point = true;
			break;
		}
}

string MinMon::name() const
{
	return "MinMon";
}
