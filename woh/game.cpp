#include "game.h"
#include <cmath>
using namespace std;



Player::~Player(){}


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

string card_play_msg(int status)
{
	switch(status)
	{
	case Succ: return "success.";
	case CLUB2_MUST_BE_FIRST_CARD: return "must play club2 in first circle.";
	case PLAY_SAME_COLOR_WITH_FIRST_PLAYER: return "must play same color's card with first player.";
	case CANNOT_PLAY_POINT_CARD_IN_FIRST_CIRCLE: return "cannot play point card in first circle.";
	case DO_NOT_OWN_CARD: return "do not own this card.";
	case CANNOT_PLAY_POINT_CARD_YET: return "cannot play point card yet";
	}
}

GameUI::~GameUI()
{}

Game::Game(GameUI* ui, vector<Player*> players) : _ui(ui), _players(players)
{
	// Round 1
	SWAP_ORDER[0][0] = Coord(0, 1);
	SWAP_ORDER[0][1] = Coord(2, 3);

	// Round 2
	SWAP_ORDER[1][0] = Coord(0, 2);
	SWAP_ORDER[1][1] = Coord(1, 3);

	// Round 3
	SWAP_ORDER[2][0] = Coord(0, 3);
	SWAP_ORDER[2][1] = Coord(1, 2);

	// Round 4
	SWAP_ORDER[3][0] = Coord(0, 0);
	SWAP_ORDER[3][1] = Coord(0, 0);
}

Game::~Game()
{}

void Game::play_card(int player, Card c)
{
	drop_card(player, c);
}

void Game::gain_point(int player, Card c)
{
	_pc[player][c] = Point;
}

void Game::drop_card(int player, Card c)
{
	_pc[player][c] = Drop;
}

void Game::drop_cards(int player, vector<Card> cards)
{
	for(auto it = cards.begin(); it != cards.end(); ++it)
		_pc[player][*it] = None;
}

void Game::rcv_cards(int player, vector<Card> cards)
{
	for(auto it = cards.begin(); it != cards.end(); ++it)
		_pc[player][*it] = Own;
}

int Game::cnt_points(int start_player, vector<Card> cards)
{
	Card max = cards[0];
	int max_player = start_player;
	int p = start_player;
	for(int i = 1; i < PLAYER_NUM; ++i)
	{
		if(++p >= PLAYER_NUM) p = 0;
		if(cards[i].c == max.c && cards[i].n > max.n)
		{
			max = cards[i];
			max_player = p;
		}
	}
	
	for(int i = 0; i < PLAYER_NUM; ++i)
		_players[i]->circle_end(max_player, cards);

	vector<Card> pts;
	for(auto it = cards.begin(); it != cards.end(); ++it)
		if(is_point_card(*it)) pts.push_back(*it);
	
	_ui->add_point(max_player, pts);
	gain_points(max_player, pts);
	return max_player;
}

void Game::gain_points(int player, vector<Card> cards)
{
	for(auto it = cards.begin(); it != cards.end(); ++it)
	{
		_score_rnd[player] += card_point(*it);
		gain_point(player, *it);
	}
	_ui->update_rnd_score(_score_rnd);
}

bool Game::check_swaps(int player, const vector<Card>& cards)
{
	if(cards.size() != 3) return true;
	for(auto it = cards.begin(); it != cards.end(); ++it)
		if(_pc[player][*it] != Own) return true;
	return false;
}


int Game::has_non_point_card(int player)
{
	bool has_nm_cards = 0;
	for(auto it = _pc[player].begin(); it != _pc[player].end(); ++it)
		if((*it).second == Own && !is_point_card((*it).first))
		{
			has_nm_cards = 1;
			break;
		}
	return has_nm_cards;
}

int Game::check_play_card(int player, const vector<Card>& cards)
{
	Card first = cards[0];
	Card played = cards[cards.size() - 1];
	const Card c2 = Card(Club, N2);

	if(first == played && is_point_card(first) && !_circle_pt_switch && has_non_point_card(player)) return CANNOT_PLAY_POINT_CARD_YET;
	// cannot play point card in first circle
	if(first == c2 && is_point_card(played) && has_non_point_card(player)) return CANNOT_PLAY_POINT_CARD_IN_FIRST_CIRCLE;
	// first card must be Club2
	if(_pc[player][c2] == Own && played != c2) return CLUB2_MUST_BE_FIRST_CARD;
	// must play same color with first
	if(first.c != played.c && exist_color(player, first.c)) return PLAY_SAME_COLOR_WITH_FIRST_PLAYER; 
	// play card witch don't own
	if(_pc[player][played] != Own) return DO_NOT_OWN_CARD;

	if(is_point_card(played)) _circle_pt_switch = 1;
	return 0;
}
int Game::exist_color(int player, u8 c)
{
	for(u8 v = N2; v <= A; ++v)
		if(_pc[player][Card(c, v)] == Own) return 1;
	return 0;
}

void Game::init()
{
	_deck.clear();
	for(u8 c = Diamond; c <= Heart; ++c)
	{
		for(u8 v = N2; v <= A; ++v)
			DECK.push_back(Card(c, v));
	}
	
	for(int p = 0; p < PLAYER_NUM; ++p)
	{
		_pc[p].clear();
		for(auto it = _deck.begin(); it != _deck.end(); ++it)
		{
			_pc[p][*it] = None;
		}
		_score_rnd[p] = 0;
		_score[p] = 0;
	}

	vector<string> names;
	for(int i = 0; i < PLAYER_NUM; ++i)
		names.push_back(_players[i]->name());
	_ui->game_start();
	_ui->init_player(names);
}

void Game::init_rnd()
{
	_deck.clear();
	for(auto it = DECK.begin(); it != DECK.end(); ++it)
		_deck.push_back(*it);

	for(int p = 0; p < PLAYER_NUM; ++p)
	{
		_pc[p].clear();
		for(auto it = _deck.begin(); it != _deck.end(); ++it)
		{
			_pc[p][*it] = None;
		}
		_score_rnd[p] = 0;
	}
	_circle_pt_switch = 0;
	_ui->round_start();
}

void Game::wash_deck()
{
	const int WASH_TIMES = 10;
	const int WASH_NUMS = 10;

	for(int i = 0; i < WASH_TIMES; ++i)
	{
		vector<Coord> swaps;
		for(int j = 0; j < WASH_NUMS; ++j)
		{
			Coord c(rand() % _deck.size(), rand() % _deck.size());
			Card x = _deck[c.x];
			Card y = _deck[c.y];
			_deck[c.x] = y;
			_deck[c.y] = x;
			swaps.emplace_back(c);
		}
		_ui->wash_cards(swaps);
	}
}

void Game::split_deck()
{
	vector<Card> pc[PLAYER_NUM];
	for(int i = 0; i < _deck.size(); i += PLAYER_NUM)
	{
		for(int p = 0; p < PLAYER_NUM; ++p)
		{
			pc[p].push_back(_deck[i + p]);
			_pc[p][_deck[i + p]] = Own; // direct oper _pc, other place call rcv_cards
			if(_deck[i + p] == Card(Club, 2)) _circle_start = p;
		}
	}

	for(int i = 0; i < PLAYER_NUM; ++i)
	{
		_players[i]->set_cards(pc[i]);
		_ui->dispatch_cards(i, pc[i]);
	}
}

void Game::do_swap()
{
	int order = _rnds % ORDER_NUM;
	if(order == 3) return;
	Coord* c = SWAP_ORDER[order];
	vector<vector<Card>> swaps(4);
	for(int i = 0; i < PLAYER_NUM; ++i)
	{
		auto& cards = _players[i]->swap(SWAP_CARD_NUM);
		if(check_swaps(i, cards)) force_end(i, "cheated in card swap.");
		swaps[i] = cards;
		drop_cards(i, cards);
		_ui->snd_swap(i, cards);
	}
	for(int i = 0; i < SWAP_NUM; ++i)
	{
		if(c[i].x == c[i].y) continue;
		_players[c[i].x]->rcv_swap(swaps[c[i].y]);
		_players[c[i].y]->rcv_swap(swaps[c[i].x]);
		
		rcv_cards(c[i].x, swaps[c[i].y]);
		rcv_cards(c[i].y, swaps[c[i].x]);
		_ui->rcv_swap(c[i].x, swaps[c[i].y]);
		_ui->rcv_swap(c[i].y, swaps[c[i].x]);
	}
}

void Game::circle()
{
	vector<Card> cc;
	int pp = _circle_start;
	for(int i = 0; i < PLAYER_NUM; ++i)
	{
		Card c = _players[pp]->play_card(cc);
		cc.push_back(c);
		int status = check_play_card(pp, cc);
		if(status) force_end(pp, card_play_msg(status));
		play_card(pp, c);
		_ui->play_card(pp, c);
		if(++pp >= PLAYER_NUM) pp = 0;
	}
	_circle_start = cnt_points(_circle_start, cc);
}

void Game::update_score()
{
	int hit_moon = -1;
	for(int i = 0; i < PLAYER_NUM; ++i)
		if(_score_rnd[i] == MAX_POINT) hit_moon = i;
	if(hit_moon > 0) for(int i = 0; i < PLAYER_NUM; ++i)
	{
		if(i == hit_moon) _score_rnd[i]  = 0;
		else _score_rnd[i] = MAX_POINT;
	}
	for(int i = 0; i < PLAYER_NUM; ++i)
		_score[i] += _score_rnd[i];
	_ui->update_score(_score_rnd, _score);
	_ui->round_end();
}

bool Game::is_end()
{
	for(int i = 0; i < PLAYER_NUM; ++i)
		if(_score[i] >= END_SCORE) return true;
	return false;
}

void Game::end()
{
	_ui->game_end(_score);
}

void Game::force_end(string msg)
{
	_ui->force_end(msg);
	exit(1);
}

void Game::force_end(int player, string msg)
{
	force_end(_players[player]->name() + ": " + msg);
}


void Game::main_loop()
{
	init();
	while(!is_end())
	{
		init_rnd();
		wash_deck();
		split_deck();
		do_swap();
		for(int i = 0; i < RND_NUM; ++i)
			circle();
		update_score();
	}
	end();
}