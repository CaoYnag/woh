#include "defs.h"


Card::Card()
{
	c = CUnset;
	n = NUnset;
}
Card::Card(u8 _c, u8 _n)
{
	c = _c;
	n = _n;
}
Card::Card(u32 _v)
{
	v = _v;
}
Card& Card::operator=(const u32& value)
{
	v = value;
	return *this;
}

bool operator<(const Card& a, const Card& b)
{
	return (a.n == b.n) ? (a.c < b.c) : (a.n < b.n);
}
bool operator!=(const Card& a, const Card& b)
{
	return !(a == b);
}
bool operator==(const Card& a, const Card& b)
{
	return (a.n == b.n) && (a.c == b.c);
}

bool is_point_card(const Card& c)
{
	return (c.c == Heart) || (c.c == Blade && c.n == Q);
}
int  card_point(const Card& c)
{
	if(c.c == Heart)
		return 1;
	else if(c.c == Blade && c.n == Q)
		return 13;
	return 0;
}

const static string CARD_COLORS_UTF[] = {"✪", "♦", "♠", "♣", "❤", "♥♠♦♣♤♡♢♧"};
const static string CARD_COLORS[] = {"X", "D", "B", "C", "H"};
const static string CARD_VALUES[] = {"✪", "✪", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
string card_str(const Card& c)
{
	return CARD_COLORS[c.c] + CARD_VALUES[c.n];
}

Coord::Coord() : x(0), y(0)
{}

Coord::Coord(u32 _x, u32 _y) : x(_x), y(_y)
{}

Coord::Coord(const Coord& c) : x(c.x), y(c.y)
{}

Coord& Coord::operator=(const Coord& c)
{
	x = c.x;
	y = c.y;
	return *this;
}

const int MAX_POINT = 26;

Score::Score()
{}

Score::Score(const string& n, u32 s) : name(n), score(s)
{}

bool operator<(const Score& a, const Score& b)
{
	return a.score < b.score;
}