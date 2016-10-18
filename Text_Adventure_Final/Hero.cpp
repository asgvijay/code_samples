//
//  Hero.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Hero.hpp"
#include <iostream>
#include <string>
using std:: cout;
using std:: endl;


// returns hero's oxy level
int Hero:: getOxyLev()
{
    return oxyLevel;
    
}

//takes int argument to adjust oxylevel variable
void Hero:: setOxyLev(int a)
{
    oxyLevel-=a;
    
}

//adds the string argument to the vector of friends
void Hero::addFriend(string a)
{
    friends.push_back(a);
    
}

//adds the string argument to the vector of keys
void Hero:: addKeys(string b)
{
    
    keys.push_back(b);
    
}


Hero:: Hero()
{
    whereAmI = NULL;
    oxyLevel=100;
    conquer = false;
    friends = {"You"};
}
//sets the whereAmI pointer to a
void Hero:: setWhere(Space* a)
{
    whereAmI = a;
    
    
}
//returns the whereAmI pointer
Space* Hero:: getWhere()
{
    return whereAmI;
    
}

//removes any " " strings from the vector
void Hero:: flushKeys()
{
    int i = 0;
    while(i< keys.size())
    {
        if(keys[i] == " ")
            keys.erase(keys.begin()+i);
        
        else
            i++;
    }
    
}

// prints out the vector of friends
void Hero:: printFriends()
{
    if(!friends.empty())
    {   for(int i = 0; i<friends.size(); i++)
            cout << friends[i] << endl;
    }
    else
        cout << "You have no friends at the moment."<< endl;
}
//prints out the vector of keys
void Hero:: printKeys()
{
    if(!keys.empty())
    {for(int i = 0; i<keys.size(); i++)
        cout << keys[i] << endl;
    }
    else
        cout << "You have no notes at the moment." << endl;
}
//prints out the vector of friends for a menu
void Hero:: chooseFriends()
{
    
    for(int i=0; i<friends.size(); i++)
            cout << "# " << i+1 << " " <<friends[i] << endl;
  
    
}
//takes the menu choice as an int and returns the string of that vector option
std:: string Hero:: friendChoice(int a)
{
    
    return friends[a-1];
    
}
//tests to see if friends list is empty
bool Hero:: isEmpty()
{
    if(friends.empty())
        return true;
    else
        return false;
    
}
//returns the vector of friends
std:: vector<string> Hero:: getFriends()
{
    return friends;
    
}
//returns the vector of keys
std:: vector<string> Hero:: getNotes()
{
    
    return keys;
}

