//
//  Hero.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Hero_hpp
#define Hero_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "Space.hpp"

using std:: vector;
using std:: string;

class Hero
{
    
    
protected:
    int oxyLevel;
    vector<string> friends;
    vector<string> keys;
    Space* whereAmI;
    bool conquer;
    
public:
    int getOxyLev();
    void setOxyLev(int a);
    void addFriend(string a);
    void addKeys(string b);
    void setWhere(Space* a);
    Space* getWhere();
    Hero();
    //bool getConquer();
    void flushKeys();
    void printFriends();
    void printKeys();
    void chooseFriends();
    void chooseKeys();
    string friendChoice(int a);
    bool isEmpty();
    //int flyHeli();
    //int goMainFrameDoor1();
    //int goMainFrameDoor2();
    //int goMainFrameDoor3();
    //void killFriend(string a);
    std:: vector<string> getFriends();
    std:: vector<string> getNotes();
};
#endif /* Hero_hpp */
