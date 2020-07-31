#pragma once
#include "defs.h"
#include "ui.h"
#include "player.h"
#include <vector>
#include <map>
#include <string>
using std::string;
using std::vector;
using std::map;

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