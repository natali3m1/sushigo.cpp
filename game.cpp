/*
 * game.cpp
 * CS11 Sushi Go
 * Name: Natalie Elliott
 * Date started: 4/16
 */

#include "game.h"
#include <fstream>
#include <iostream>

//constructor, reads in file data into vector deck
Game::Game(string filename, string play_chopsticks){
    if(play_chopsticks == "true") this->play_chopsticks = true; //bonus
    else this->play_chopsticks = false; 
    ifstream infile(filename);
    if (infile.fail()){
        cerr << "file won't open!";
        exit(EXIT_FAILURE);
    }
    string nonsense, type; //accounting for titles in data files
    infile >> nonsense >> nonsense;
    int worth = 0, cardNum = 0; //positive for maki, sufficient deck check
    infile >> type;
    while (!infile.eof()){
        if (type == "Chopsticks"){
            if (this->play_chopsticks){
                Card *card = new Card(type, 0); //move on to the next, 
                //discard chops
                deck.insert(0, card);
                cardNum++;
                continue;
            }
        }
        else if (type == "Maki"){
            infile >> worth; //bc maki have 1, 2, or 3
            Card *card = new Card(type, worth); //constructor
            deck.insert(0, card); //put it at the "top" of the deck
            cardNum ++;
        }
        else{
            Card *card = new Card(type, 0); //no worth bc not maki
            deck.insert(0, card); 
            cardNum ++;
        }
        infile >> type; //cont
    }
    if(cardNum < 81){ //sufficient deck check
        cerr << "ERROR: Not enough cards to play!" << endl;
        exit(EXIT_FAILURE);
    }
    deckIndex = 0;
}

/* dealHands
 * Input: n/a
 * Description: deals 27 cards to 3 players
 * Output: n/a
 */
void Game::dealHands(){
    for(int i = 0; i < CARD_HAND; i++){
        for(int player = 0; player < PLAYER_COUNT; player++){
            Vector *passing_hand = players[player].getPassingHand();
            passing_hand->pushback(deck.at(deckIndex)); 
            deckIndex++;  //track unm cards
            }
        } 
}
/* chopsticks
 * Input: player num, vector pointer with chosen card, 
 int card index, vector pointer with passing hand
 * Description: if someone wants to use their chopsticks
 calls chophelp
 * Output: n/a
 */
void Game::chopsticks(int player, Vector *temp_reveal_card, 
    int card_index, Vector *passing_hand){
    bool usedChopsticks = false;
    if (haveChops(player) && !usedChopsticks) {
        cout << "     " << temp_reveal_card->at(0)->getSushiType()
        << " selected!" << endl; //only if have chops you announce chosen
        cout << "     Would you like to use your Chopsticks card";
        cout << " to select a second card from your hand? (y/n): ";
        string choice;
        cin >> choice;
        int first_choice = card_index;
        if (choice == "y") {
            usedChopsticks = true; //to remove for later
            int second_index;
            helperChop(second_index, passing_hand, card_index); //helper
            Card *second = passing_hand->at(second_index-1); //second
            passing_hand->remove(second_index - 1);
            temp_reveal_card->pushback(second); //put in temp to reveal
            useChopsticks(player); //call help
        }
    }
}
/* helperChop
 * Input: address int to edit, vector pointer to
 player hand, integer of card index
 * Description: lets use chopsticks
 custom error messages
 * Output: n/a
 */
void Game::helperChop(int &s, Vector *p_h, int c){
    cout << "     Select a second card: ";
    while (1) {
        cin >> s;
        if (!cin) {
            cerr << " INVALID INPUT: No game for you!\n";
            exit(EXIT_FAILURE);
        }
        int u = p_h->size();
        int v = c + 1; //in player-terms
        if (s == v) {
            cout << "     That card has already been selected.\n";
            cout << "     Please enter a valid number between 1 and "
                << u << " (other than " << v << "): " << endl;
            continue;
        }
        if (s <= 0 || s > u) { //custom chopsticks error messages below
            if (v == 1) {
                cout << "     Please enter a valid number between 2 and "
                    << u << ": ";
            }
            else if (v == u) {
                cout << "     Please enter a valid number between 1 and "
                    << u - 1 << ": ";
            }
            else {
                cout << "     Please enter a valid number between 1 and "
                    << u << ": ";
            }
            continue;
        }
        break;//when valid answer
    }
}


/* pickAndPass
 * Input: n/a
 * Description: allows players to pick one card
 * then pass their hand to the right (1->2)
 * Output: n/a
 */
void Game::pickAndPass(){
    int card_index;
    while (players[0].getPassingHand()->size() > 0){
        for(int player = 0; player < PLAYER_COUNT; player++){
            board.drawBoard(players, player); //draw hands
            Vector *passing_hand = players[player].getPassingHand();
            Vector *temp_reveal_card = players[player].getTempCard();
            cout << " Player " << player + 1 << ", select a card: ";
            while (1) { //loop til break (not pretty but works)
                cin >> card_index;
                if (!cin) {
                    cerr << " INVALID INPUT: No game for you!\n";
                    exit(EXIT_FAILURE);
                }
                if (card_index > 0 && card_index <= passing_hand->size()) {
                    break;
                }
                cout << "     Please enter a valid number between 1 and "
                    << passing_hand->size() << ": ";
            }
            int index = card_index - 1;
            Card *chosen = passing_hand->at(index);
            temp_reveal_card->pushback(chosen);
            passing_hand->remove(index);
            chopsticks(player, temp_reveal_card, index, passing_hand);
        }
        Vector temp = *players[PLAYER_COUNT - 1].getPassingHand(); //save last
        for(int i = 2; i > 0; i--){
            *players[i].getPassingHand() = 
            *players[i - 1].getPassingHand();
        }
        *players[0].getPassingHand() = temp; //first = last
        printRevealed();
        for(int player = 0; player < PLAYER_COUNT; player++){
            players[player].getTempCard()->clear(); //clears chosen card vector
        }
    }
}
/* useChopsticks
 * Input: player num
 * Description: takes off chopsticks and adds to passing
 * Output: n/a
 */
void Game::useChopsticks(int player) {
    Vector *revealed = players[player].getRevealedCards();
    Vector *passing = players[player].getPassingHand();
    for (int i = 0; i < revealed->size(); i++) {
        if (revealed->at(i)->getSushiType() == "Chopsticks") {
            Card *chop = revealed->at(i); //find chop in hand
            revealed->remove(i); //remove it
            passing->pushback(chop); //put it in pass hand
            return;
        }
    }
}
/* haveChops
 * Input: player num
 * Description: if you have a chopsticks in your hand
 * Output: true if chopsticks possessed
 */
bool Game::haveChops(int player){
    Vector *revealed = players[player].getRevealedCards();
    for (int i = 0; i < revealed->size(); i++){
        if (revealed->at(i)->getSushiType() == "Chopsticks"){
            return true; //if you own a chopstick
        }
    }
    return false;
}

/* printRevealed
 * Input: n/a
 * Description: reveals cards everyone chose
 * Output: n/a
 */
void Game::printRevealed(){
    for(int player = 0; player < PLAYER_COUNT; player++){
        Vector *revealed = players[player].getRevealedCards();
        Vector *temp = players[player].getTempCard();
        for(int i = 0; i < temp->size(); i++){
            revealed->pushback(temp->at(i));
        }
    }
}
//main game loop, plays three rounds of sushi go
/* playGame
 * Input: n/a
 * Description: plays 3 rounds of sushigo
 * Output: n/a
 */
void Game::playGame(){
    string play_on;
    for(int round = 0; round < ROUNDS; round++){ //3 rounds
    /*   Deal 9 cards to each player          */
        dealHands();
        //select and pass all 27 cards
        pickAndPass();          // players choose cards + build temp hands
        scoring_time();         // compute scores from revealed hands
        board.drawScore(players); // display updated scores
        if(round < 2){
            cout << " End of round! Ready for Round "
                 << round + 2 << " ? (y/n): ";
            cin >> play_on;
            if(play_on != "y"){
                break;
            }
        }                                                        
        round_reset(); //reset for next round
    }
    collect_puddings();
    int best = numWinner(); //player winner index
    board.drawWinner(players, best); //print winner
}

/* numWinner
 * Input: n/a
 * Description: if there's one clear winner, return their index in players
 * Output: winner's index
 */
int Game::numWinner(){
    int winning = players[0].getScore(); //top score tracker
    int bestPlayer = 0;
    for(int i = 1; i < PLAYER_COUNT; i++){
        if(players[i].getScore() > winning){
            winning = players[i].getScore();
            bestPlayer = i; //might be more than one
        }
    }
    int tieCount = 0;
    for(int i = 0; i < PLAYER_COUNT; i++){
        if(players[i].getScore() == winning){
            tieCount ++; //how many people are tied for top
        }
    }
    if (tieCount == 1){
        return bestPlayer;
    }
    else{
        return tieBreaker(winning); //either -1 if pudding tied too or index
        //of most puddings' player
    }
}
/* tieBreaker
 * Input: int best score
 * Description: either breaks tie
 * with pudding counts or returns lame (-1)
 * Output: either -1 if everything tied or true winner's index
 */
int Game::tieBreaker(int bestScore){
    int tied[PLAYER_COUNT]; //will contain indeces of tied
    int tieCount = 0;
    for(int i = 0; i < PLAYER_COUNT; i++){
        if(players[i].getScore() == bestScore){
            tied[tieCount] = i; //put tied player indeces in array
            tieCount++; //if == 2, one tie, if == 3, all tied
        }
    }
    int best = tied[0]; //track top puddings' index
    for(int i = 1; i < tieCount; i++){
        int other = tied[i]; //other person
        if(players[other].getPuddingCount() > players[best].getPuddingCount()){
            best = other; // find max pudding among tied players
        }
    }
    int maxPudding = players[best].getPuddingCount();
    int puddingTieCount = 0;
    for(int i = 0; i < tieCount; i++){
        if(players[tied[i]].getPuddingCount() == maxPudding){
            puddingTieCount++; //if > 1, LAME doesn't matter if two or three
        }
    }
    if(puddingTieCount > 1){
        return -1; // tied in both score and pudding!!!
    }
    return best; //if not tied in both ways, return pudding winner
}

/* collect_puddings
 * Input: n/a
 * Description: updates scores based on # of puddings!
 * Output: n/a
 */
void Game::collect_puddings(){ //for scoring purposes, not ties
    int puddingCount[PLAYER_COUNT]; //save all three pudding counts
    for(int i = 0; i < PLAYER_COUNT; i++){
        puddingCount[i] = players[i].getPuddingCount();
    }
    bool same = true; //check if they're all equal (divvy points equally)
    for(int i = 1; i < PLAYER_COUNT; i++){
        if(puddingCount[i] != puddingCount[0]){
            same = false;
            break;
        }
    }
    if(!same){ //if not the same
        int topPCount = puddingCount[0]; //for now
        int worstPCount = puddingCount[0];
        for(int i = 1; i < PLAYER_COUNT; i++){ //most and least puddings
            if(puddingCount[i] > topPCount) topPCount = puddingCount[i];
            if(puddingCount[i] < worstPCount) worstPCount = puddingCount[i];
        }
        int numTopPudds = 0, numWorstPudds = 0; //how many ties
        for(int i = 0; i < PLAYER_COUNT; i++){
            if(puddingCount[i] == topPCount) numTopPudds++; //how many
            //players have the most puddings
            if(puddingCount[i] == worstPCount) numWorstPudds++; //and worst
        }
        int yay = 6 / numTopPudds; //integer division ignore remainders
        for(int i = 0; i < PLAYER_COUNT; i++){
            if(puddingCount[i] == topPCount){
                players[i].setScore(yay); //set points
            }
        }
        int sucks = -(6 / numWorstPudds); //make it negative
        for(int i = 0; i < PLAYER_COUNT; i++){
            if(puddingCount[i] == worstPCount){
                players[i].setScore(sucks); //set negative points
            }
        }
    }
}
/* round_reset
 * Input: n/a
 * Description: erases temporary card (chosen card),
 * their dealt hands, and their revealed cards
 * Output: n/a
 */
void Game::round_reset(){
    for(int p = 0; p < PLAYER_COUNT; p++){
        players[p].clearTempCard(); //clears chosen vector
        players[p].clearPassingHand(); //clears passing
        players[p].clearRevealedCards(); //clears revealed
    }
}
/* maki_scoring
 * Input: integer array of # of makis owned per player
 * Description: assigns points based on who has most 
 * and least amount of makis
 * Output: n/a
 */
void Game::maki_scoring(int maki_totals[]){
    int first = -1, second = -1; //nonsense num makis
    for(int i = 0; i < PLAYER_COUNT; i++){
        if(maki_totals[i] > first){
            second = first; //sorting
            first = maki_totals[i];
        }
        else if(maki_totals[i] > second && maki_totals[i] < first){
            second = maki_totals[i]; //sorting
        }
    }
    int numMostMakis = 0, numSecondBest = 0; //ties tbd
    for(int i = 0; i < PLAYER_COUNT; i++){
        if(maki_totals[i] == first) numMostMakis++; //how many ppl
        //tie for most
        if(maki_totals[i] == second) numSecondBest++; //or worst
    }
    if(numMostMakis > 1){ //no second place rewards!!!
        int points = 6 / numMostMakis;
        for(int i = 0; i < PLAYER_COUNT; i++){
            if(maki_totals[i] == first){
                players[i].setScore(points);
            }
        }
    }
    else{
        for(int i = 0; i < PLAYER_COUNT; i++){
            if(maki_totals[i] == first){
                players[i].setScore(6); //just the one winner
            }
        }
        if(second > 0){ //if tied for second
            int points = 3 / numSecondBest; //most it can be is 2 
            for(int i = 0; i < PLAYER_COUNT; i++){
                if(maki_totals[i] == second){
                    players[i].setScore(points);
                }
            }
        }
    }
}
/* scoring_time
 * Input: n/a
 * Description: tracks number of cards per category
 * then calls helper scoring functions
 * Output: n/a
 */
void Game::scoring_time(){
    int maki_totals[PLAYER_COUNT] = {0}; //array of maki vals
    for (int player = 0; player < PLAYER_COUNT; player++){
        Vector *revealed_hand = players[player].getRevealedCards();
        int temp_count = 0, puddings = 0, 
        sashimi_count = 0, dump_count = 0;
        for(int i = 0; i < CARD_HAND; i++){
            Card *scoring = revealed_hand->at(i); //card by card
            if(scoring->getSushiType() == "Maki"){
                maki_totals[player] += scoring->getMakiCount();
            } //saving in array bc have to sort points later
            else if(scoring->getSushiType() == "Tempura"){
                temp_count +=1; //tempura
            }
            else if(scoring->getSushiType() == "Sashimi"){
                sashimi_count += 1; //sashimi
            }
            else if(scoring->getSushiType() == "Dumpling"){
                dump_count += 1; //dumplings
            }
            else if(scoring->getSushiType() == "Pudding"){
                puddings += 1; //puddings

            }
            else{ //not really necessary but idk if the data
                //might have bad inputs (or chopsticks)
                continue;
            }
        } //below are all the functions for scoring cards (except maki)
        players[player].setScore(wasabi_nigiri_scoring(revealed_hand));
        players[player].setScore(players[player].temp_score(temp_count));
        players[player].setScore(players[player].sashimi_score(sashimi_count));
        players[player].setScore(players[player].dump_score(dump_count));
        players[player].addPudding(puddings);
    }
    maki_scoring(maki_totals); //have to put maki after every player has been
    //evaluated because it's a relative scoring process
}
/* wasabi_nigiri_scoring
 * Input: vector pointer
 * Description: pair wasabi and nigiri
 * if wasabi is drawn first
 * Output: updated nigiri score
 */
int Game::wasabi_nigiri_scoring(Vector *revealed_hand){
    int score = 0;
    int wasabis = 0;
    for(int i = 0; i < CARD_HAND; i++){
        Card *card = revealed_hand->at(i);
        string type = card->getSushiType();

        if(type == "Wasabi"){
            wasabis++;
        }
        else if(type == "Egg-Nigiri" || type == "Salmon-Nigiri" 
            || type == "Squid-Nigiri"){ //if it's a nigiri
            int value = card->getNigiriValue();

            if(wasabis > 0){ //if there's an available wasabi
                score += value * 3;
                wasabis--; //"delete" wasabi (not the actual card)
            } else {
                score += value; //to be returned
            }
        }
    }
    return score; //to give to set score func
}

//destructor
Game::~Game(){
    for (int i = 0; i < deck.size(); i++) {
        delete deck.at(i); //deck has all cards
        //so delete them all!! even when "moved"
        //into playing/revealed/temp hands they're actually 
        //all still in the deck bc pointers
    }
}
