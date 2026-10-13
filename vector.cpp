 /*
 * vector.cpp
 * Name: Natalie Elliott
 * Date started: 4/16
*/
#include "vector.h"

//constructor
Vector::Vector(){
}
//destructor
Vector::~Vector(){
    //delete stuff;
}
void Vector::clear(){
    stuff.clear(); //erase the vector entirely, but not the actual cards
}
/* insert
 * Input: index and card pointer
 * Description: puts a card into the vector at the given
index except i only put stuff at the front
but for some reason can't just put index = 0
 * Output: n/a
 */
void Vector::insert(int index, Card *card){
    stuff.insert(stuff.begin() + index, card);
} 
/* reveal
 * Input: vector pointer
 * Description: returns first card
 * pointer in vector passed in, then
 * deletes it (for reveal delay)
 * Output: card pointer
 */
Card *Vector::reveal(Vector *temp){
    Card *hey = temp->at(0); //should only be
    //one thing in there since no chopsticks yet
    temp->remove(0);
    //delete it to empty up vector
    return hey; //just one card bc no chops
}
/* remove
 * Input: index
 * Description: erases thing at index
 * Output: n/a
 */
void Vector::remove(int index){
    stuff.erase(stuff.begin() + index);
}
/* pushback
 * Input: card pointer
 * Description: puts card at end of vector
 * Output: n/a
 */
void Vector::pushback(Card *card){
    stuff.push_back(card);
}
/* size
 * Input: na
 * Description: returns vector size
 * Output: int vector size
 */
int Vector::size(){
    return stuff.size();
}
/* at
 * Input: index
 * Description: finds card pointer at index
 * Output:returns card pointer
 */
Card* Vector::at(int index){
    return stuff.at(index);
}