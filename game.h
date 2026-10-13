/*
 * game.h
 * COMP11 Sushi Go
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "board.h"
#include "vector.h"
#include "player.h"
using namespace std;

class Game{
    public:
        //constructor/destructor
        Game(string filename, string play_chopsticks);
        ~Game();

        //main gameplay
        void playGame();
        //dealing

    private:
        void dealHands();
        bool haveChops(int p);
        void useChopsticks(int p);
        //playing
        void pickAndPass();
        //show
        void printRevealed();
        int numWinner();
        //scoring
        void scoring_time();
        int wasabi_nigiri_scoring(Vector *revealed_hand);
        void round_reset();
        void collect_puddings();
        int tieBreaker(int bestScore);
        void maki_scoring(int arr[]);
        void chopsticks(int player, Vector *temp_reveal_card, 
        int card_index, Vector *passing_hand);
        void helperChop(int &s, Vector *p_h, int c);
        //constants
        static const int PLAYER_COUNT = 3;
        static const int ROUNDS = 3;
        static const int CARD_HAND = 9;

        //chopsticks activated true/false
        bool play_chopsticks;

        //card deck
        Vector deck;

        //game objects
        Board board;
        Player players[PLAYER_COUNT];
        //deck tracker
        int deckIndex;
};

#endif
