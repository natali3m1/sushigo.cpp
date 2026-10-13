//card.h

#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card{
    public:
        //constructor
        Card(string type, int worth);
        //destructor
        ~Card();
        //methods
        string getSushiType();
        int getMakiCount();
        int getNigiriValue();
    private:
        //card info
        string name;
        int points;
};


#endif
