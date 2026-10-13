//player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "vector.h"

using namespace std;

class Player{
    public:
        //constructor
        Player();
        //destructor
        ~Player();
        //methods
        Vector* getRevealedCards();
        Vector* getPassingHand();
        int temp_score(int t);
        int sashimi_score(int s);
        int dump_score(int d);
        Vector* getTempCard();
        void addPudding(int puddings);
        int getScore();
        void setScore(int points);
        int getPuddingCount();
        void clearPassingHand();
        void clearTempCard();
        void clearRevealedCards();
        Vector* get_maki_totals();
    private:
        //objects
        Vector passingHand;
        Vector temp_reveal_card;
        Vector revealedHand;
        Vector maki_totals;
        //info
        int playernum;
        int score;
        int puddings;
};


#endif
