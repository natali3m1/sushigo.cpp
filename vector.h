//vector.h

#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

#include "card.h"
#include <vector>

class Vector{
    public:
        //constructor
        Vector();
        //destructor
        ~Vector();
        //methods
        void clear();
        void pushback(Card *card);
        void insert(int index, Card *card);
        Card *reveal(Vector *temp);
        Card* at(int);
        void remove(int index);
        int size();
    private:
        //object is a vector of card pointers
        vector<Card*> stuff;
};

#endif
