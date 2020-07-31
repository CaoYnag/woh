#include "xcui.h"
#include <cstdlib>
#include <ctime>

ExCUI::ExCUI()
{
    
}

 ExCUI::~ExCUI()
 {
 }

 void ExCUI::init_player(vector<string> player)
 {
	 _players = player;
 }

 void ExCUI::game_start()
 {
    ConsoleUI::game_start();
 }

 void ExCUI::round_start()
 {
	ConsoleUI::round_start();
 }

 void ExCUI::wash_cards(vector<Coord> swaps)
 {
     ConsoleUI::wash_cards(swaps)
 }

 void ExCUI::dispatch_cards(int sit, vector<Card> cards)
 {
     ConsoleUI::dispatch_cards(sit, cards);
 }

 void ExCUI::snd_swap(int sit, vector<Card> cards)
 {
     ConsoleUI::snd_swap(sit, cards);
 }

 void ExCUI::rcv_swap(int sit, vector<Card> cards)
 {
     ConsoleUI::rcv_swap(sit, cards);
 }

 void ExCUI::play_card(int sit, Card c)
 {
     ConsoleUI::play_card(sit, c);
 }

 void ExCUI::add_point(int sit, vector<Card> points)
 {
     ConsoleUI::add_point(sit, points);
 }

 void ExCUI::update_rnd_score(int* scores)
 {
     ConsoleUI::update_rnd_score(scores);
 }

 void ExCUI::update_score(int* new_score, int* total)
 {
     ConsoleUI::update_score(new_score, total);
 }

 void ExCUI::round_end()
 {
     ConsoleUI::round_end();
 }

 void ExCUI::game_end(int* total)
 {
     ConsoleUI::game_end(total);
 }

 void ExCUI::force_end(string msg)
 {
     ConsoleUI::force_end(msg);
 }