#pragma once
#include <vector>
#include <map>
#include <string>
using std::string;
using std::vector;
using std::map;

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

class ConsoleUI : public GameUI
{
	vector<string> _players;
	int _rnd;
public:
	virtual ~ConsoleUI();

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

enum OwnCard
{
	None,
	Drop,
	Own,
	Point
};
enum CardPlayStatus
{
	Succ = 0,
	CLUB2_MUST_BE_FIRST_CARD,
	PLAY_SAME_COLOR_WITH_FIRST_PLAYER,
	CANNOT_PLAY_POINT_CARD_IN_FIRST_CIRCLE,
	DO_NOT_OWN_CARD,
	CANNOT_PLAY_POINT_CARD_YET
};
string card_play_msg(int status);

class Game
{
public:
	static const int END_SCORE = 100;
	static const int PLAYER_NUM = 4;
	static const int ORDER_NUM = 4;
	static const int SWAP_NUM = PLAYER_NUM / 2;
	static const int SWAP_CARD_NUM = 3;
	static const int DECK_CARD_NUM = 52;
	static const int FULL_HANDS_CARD_NUM = DECK_CARD_NUM / PLAYER_NUM;
	static const int RND_NUM = FULL_HANDS_CARD_NUM;
private:
	Coord SWAP_ORDER[ORDER_NUM][SWAP_NUM];
	vector<Card>	DECK;

	vector<Card>	_deck;
	map<Card, int>	_pc[PLAYER_NUM];
	int				_rnds;
	GameUI*			_ui;
	int				_score_rnd[PLAYER_NUM];
	int				_score[PLAYER_NUM];
	vector<Player*>	_players;
	int				_circle_start;
	int				_circle_pt_switch;

	// init all
	void	init();
	void	init_rnd();
	void	wash_deck();
	void	split_deck();
	void	do_swap();
	void	circle();
	void	update_score();
	bool	is_end();
	void	end();
	void	force_end(string msg);
	void	force_end(int player, string msg);

	/*=============some utils=============*/
	void	play_card(int player, Card c);
	void	gain_point(int player, Card c);
	void	drop_card(int player, Card c);
	void	drop_cards(int player, vector<Card> cards);
	void	rcv_cards(int player, vector<Card> cards);
	int		cnt_points(int start_player, vector<Card> cards);
	void	gain_points(int player, vector<Card> cards);
	bool	check_swaps(int player, const vector<Card>& cards);
	int		check_play_card(int player, const vector<Card>& cards);
	int		exist_color(int player, u8 color);
	int		has_non_point_card(int player);
public:
	Game(GameUI* ui, vector<Player*> players);
	~Game();

	// play game, util a player reach score 100
	void	main_loop();
};