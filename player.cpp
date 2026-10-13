//player.cpp
 /*
 * player.cpp
 * Name: Natalie Elliott
 * Date started: 4/16
*/
#include "player.h"
//constructor
Player::Player(){
    score = 0;
    puddings = 0;
}
//destructor
Player::~Player(){
}
/* temp_score
 * Input: num tempura
 * Description: score based on tempura rules
 * Output:returns tempura points
 */
int Player::temp_score(int t){
    int pairs = t/2;
    int score = pairs*5;
    return score;
}
/* sashimi_score
 * Input: num sashimis
 * Description: score based on sashimi rules
 * Output:returns sashimi points
 */
int Player::sashimi_score(int s){
    int triples = s/3;
    int score = triples*10;
    return score;
}
/* dump_score
 * Input: num dumplings
 * Description: score based on dumpling rules
 * Output:returns dumpling points
 */
int Player::dump_score(int d){
    if (d >= 5) return 15;
    if (d == 4) return 10;
    if (d == 3) return 6;
    if (d == 2) return 3;
    if (d == 1) return 1;
    return 0;
}
/* clearTempCard
 * Input: n/a
 * Description: clears vector containing chosen card pointer
 * Output:returns sashimi points
 */
void Player::clearTempCard(){
    temp_reveal_card.clear();
}
/* addPudding
 * Input: num puddings
 * Description: updates player's pudding count
 * Output:n/a
 */
void Player::addPudding(int p){
    puddings += p;
}
/* clearRevealedCards
 * Input: n/a
 * Description: clears vector of revealed hand
 * Output:n/a
 */
void Player::clearRevealedCards(){
    revealedHand.clear();
}
/* clearPassingHand
 * Input: n/a 
 * Description: clears vector of passing hand
 * Output: n/a
 */
void Player::clearPassingHand(){
    passingHand.clear();
}
/* setScore
 * Input: points to be added
 * Description: updates player's score count
 * Output: n/a
 */
void Player::setScore(int points){
    score += points;
}
/* getRevealedCards
 * Input: n/a
 * Description: accesses private vector
 * Output: returns vector
 */
Vector* Player::getRevealedCards(){
    return &revealedHand;
}
/* getPassingHand
 * Input: n/a
 * Description: accesses private vector
 * Output: returns vector
 */
Vector* Player::getPassingHand(){
    return &passingHand;
}
/* getTempHand
 * Input: n/a
 * Description: accesses private vector
 * Output: returns vector
 */
Vector* Player::getTempCard(){
    return &temp_reveal_card;
}
/* get_maki_totals
 * Input: n/a
 * Description: accesses private vector
 * Output:returns vector
 */
Vector *Player::get_maki_totals(){
    return &maki_totals;
}
/* getScore
 * Input: n/a
 * Description: accesses private int
 * Output: returns score
 */
int Player::getScore(){
    return score;
}
/* getPuddingCount
 * Input: n/a
 * Description: accesses private int
 * Output: returns puddings
 */
int Player::getPuddingCount(){
    return puddings;
}