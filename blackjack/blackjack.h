//
// Created by jluna on 3/29/2023.
//

#ifndef BLACKJACK_BLACKJACK_H
#define BLACKJACK_BLACKJACK_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include<algorithm>
#include <fstream>

using namespace  std;

//a class that provides essential deck functionality
class generaldeckfunctions{
public:
    static void shuffledeck(vector<string> &d); //shuffle the deck
    static vector<string> initalizedeck(); //initialize the deck as a vector of strings
     static void printdeck(vector<string>&d); //debug function that prints out the contents of the deck

};

class deck{
public:
    deck(); //default constructor
    ~deck(); //default deconstructor
    void replacedeck();//put back the used cards back into the deck
    void discard(const string& card); //takes cards from hand and put them into a discard pile
    vector<string> d; //the global deck used for the game
    vector<string> usedpile; //discarded card pile
};

class hand{
public:
    explicit hand(deck *newdeck,bool d); //constructor for a hand
    ~hand(); //deconstructor for a hand
    void updatehandvalue(string ch); //updates and calculates the value of the hand
    bool Iwilldraw(int policy) ; //the decision policy function to see if the gambler will draw or not
    void drawcard(); //draws a card from the deck
    void prindhand(); //debug function to print the cards in hand
    void discardhand(); //discard the hand and place them into the discard pile for next game
    int handvaluegetter() const; //return the value of the hand to table class
    vector<string> cardsinhandgetter(); //returns the cards in hand
    void handvaluesetter(int x); //special case hand value update function for policy 2
    deck* carddeck; //get the global deck

private:
    bool regulardeck;//if true treat deck as a regular deck, else its an infinite deck
    vector<string> cardsinhand; //the cards in hand
    int handvalue; //value of the hand

};

class gametable{
public:
    gametable(int p,bool d);//constructor with the ability to set the policy
    ~gametable();//clean up the table
    void playgame(); //let's play a game of black jack
    void dealhands() const; //deal the first 4 cards to the players
    void gamblerdraws() const;//unique function that has the gambler draw a card
    void whowonthegame();//display the game statistics of who won
    void gamestatistics() const;//show the statistics of the game
    hand* gambler; //the player
    hand* dealer; //the house
    deck* tabledeck; //the casino
private:
    int gamblerwins;
    int dealerwins;
    int totalgames;
    int policynumber;
};

class Policy2{
public:
    static bool blackjack(const vector<string>&cardsinh, int valueofh); //check if the hand has a blackjack
    static int newhandvalue(const vector<string>&cardsinh);
    //update the new hand if it is not a blackjack, changes Ace from 11 value to value of 1
};
class Policy4{
public:
    static bool nomorethan3cards(const vector<string>&cardsinh); //draw no more than 3 cards
};
#endif //BLACKJACK_BLACKJACK_H
