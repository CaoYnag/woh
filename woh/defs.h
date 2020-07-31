#pragma once
#include <string>
using std::string;

typedef unsigned char u8;
typedef unsigned int u32;
enum Color
{
	CUnset,
	Diamond,
	Blade,
	Club,
	Heart,
};
enum Number
{
	NUnset,
	N2 = 2, N3, N4, N5, N6, N7, N8, N9, N10, J, Q, K, A, Joker
};
enum Sit
{
	East = 0,
	South,
	West,
	North
};

union Card
{
	u32 v;
	struct
	{
		u8 c;
		u8 n;
	};
	Card& operator=(const u32&);
	Card();
	Card(u8 _c, u8 _n);
	Card(u32 _v);
};
bool	operator<(const Card&, const Card&);
bool	operator==(const Card&, const Card&);
bool	operator!=(const Card&, const Card&);
bool	is_point_card(const Card&);
int		card_point(const Card&);
string  card_str(const Card&);
extern const int MAX_POINT;

struct Coord
{
	u32 x, y;

	Coord();
	Coord(u32 _x, u32 _y);
	Coord(const Coord&);
	Coord& operator=(const Coord&);
};

struct Score
{
	string	name;
	u32		score;

	Score();
	Score(const string&, u32);
};
bool operator<(const Score&, const Score&);