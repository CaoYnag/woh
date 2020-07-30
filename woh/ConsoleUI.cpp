#include "game.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


void show_cards(const vector<Card>& cards)
{
	 for(auto it = cards.begin(); it != cards.end(); ++it)
		 cout << " " << card_str(*it);
	 cout << endl;
}

 ConsoleUI::~ConsoleUI()
 {
 }

 void ConsoleUI::init_player(vector<string> player)
 {
	 _players = player;
 }

 void ConsoleUI::game_start()
 {
	 cout << "========================Game Start========================" << endl;
	 _rnd = 0;
 }

 void ConsoleUI::round_start()
 {
	 cout << "------------------------Round " << ++_rnd  << "----------------------" << endl;
 }

 void ConsoleUI::wash_cards(vector<Coord> swaps)
 {
	 cout << "washing cards..." << endl;
 }

 void ConsoleUI::dispatch_cards(int sit, vector<Card> cards)
 {
	 cout << "Cards: " << _players[sit];
	 show_cards(cards);
 }

 void ConsoleUI::snd_swap(int sit, vector<Card> cards)
 {
	 cout << "SWAP: " << _players[sit] << " >> ";
	 show_cards(cards);
 }

 void ConsoleUI::rcv_swap(int sit, vector<Card> cards)
 {
	 cout << "SWAP: " << _players[sit] << " << ";
	 show_cards(cards);
 }

 void ConsoleUI::play_card(int sit, Card c)
 {
	 cout << _players[sit] << " > " << card_str(c) << endl;
 }

 void ConsoleUI::add_point(int sit, vector<Card> points)
 {
	 if(points.size() <= 0) return;
	 cout << _players[sit] << " <";
	 show_cards(points);
 }

 void ConsoleUI::update_rnd_score(int* scores)
 {
	 cout << "Scores Now:\n";
	 for(int i = 0; i < Game::PLAYER_NUM; ++i)
	 {
		 cout << _players[i] << " : " << scores[i] << endl;
	 }
	 cout << endl;
 }

 void ConsoleUI::update_score(int* new_score, int* total)
 {
	 
	 cout << "Round " << _rnd << " Scores:\n";
	 for(int i = 0; i < Game::PLAYER_NUM; ++i)
	 {
		 cout << _players[i] << " : " << new_score[i] << "\t: " << total[i] << endl;
	 }
	 cout << endl;
 }

 void ConsoleUI::round_end()
 {
	 cout << "----------------------Round " << _rnd  << " End--------------------" << endl;
 }

 void ConsoleUI::game_end(int* total)
 {
	 cout << "=========================Game End=========================" << endl;
	 vector<Score> score(4);
	 for(int i = 0; i < Game::PLAYER_NUM; ++i)
		 score[i] = Score(_players[i], total[i]);
	 sort(score.begin(), score.end());

	 cout << "Rank\tName\tScore" << endl;
	 for(int i = 0; i < Game::PLAYER_NUM; ++i)
		 cout << i << "\t" << score[i].name << "\t" << score[i].score << endl;
 }

 void ConsoleUI::force_end(string msg)
 {
	 cout << "Game Force Ended: " << msg << endl;
 }