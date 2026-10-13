//card.cpp
 /*
 * card.cpp
 * Name: Natalie Elliott
 * Date started: 4/16
*/
#include "card.h"
//constructor
Card::Card(string type, int worth){
    name = type;
    points = worth; //0 unless maki
}
//destructor
Card::~Card(){
}
/* getSushiType
 * Input: n/a
 * Description: accesses private name
 * Output: name
 */
string Card::getSushiType(){
    return name;
}
/* getMakiCount
 * Input: n/a
 * Description: access private points
 * Output: points for maki
 */
int Card::getMakiCount(){
    return points;
}
/* getNigiriValue
 * Input: n/a
 * Description: access private name and determine
 * what point amount it relates to
 * Output:returns points based on which nigiri
 */
int Card::getNigiriValue(){
    if(name == "Egg-Nigiri") return 1;
    if(name == "Salmon-Nigiri") return 2;
    if(name == "Squid-Nigiri") return 3;
    return 0;
}