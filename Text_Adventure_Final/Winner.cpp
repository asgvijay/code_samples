//
//  Winner.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Winner.hpp"


#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Winner:: Winner()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "1234";
    spaceName = "Winner";
    
    options = { std::make_pair("Talk to the lady", 1), std:: make_pair("Talk to the Bum",2), std:: make_pair("Pick up Key",3),std:: make_pair("Go into the Bar", 4), std::make_pair("Go into the Diner",5), std::make_pair("Go Into the Library",6), std::make_pair("Go into the airport.", 7), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9) };
    
}

std:: string Winner:: beFriend()
{
    
    cout << "You just made friends with Joe Kipp the Bum." << endl;
    cout << "Joe has been added to your friend list." << endl;
    madeFriend = true;
    return people;
    
    
}
int Winner:: badDecision()
{
    cout << "You just made a bad decision. Twenty points have been deducted from your Oxy Level." << endl;
    return 20;
    
}

std::string Winner:: getKey()
{
    
    if(madeFriend)
    {
        cout << "You found a key. It's been stored in your notebook." << endl;
        return keys;
    }
    else
    {    cout << "The bum smacks your hand and tells you to BACK OFF!" << endl;
        return " ";
    }
    
}


Space* Winner:: moveOn(int a)
{
    if(a==4)
        return spaceName1;
    else if(a==5)
        return spaceName2;
    else if(a==6)
        return spaceName3;
    else
        return spaceName4;
    
}

void Winner:: roomOptions()
{
    cout << "***********************************************" << endl;
    cout << "             " <<getSpaceName()<< "            " << endl;
    cout << "***********************************************" << endl;
    cout << endl;
    cout << "You are in a seemlingly deserted intersection of a desolate city.";
    cout << "What would you like to do? " << endl;
    printOptions();
    
}

void Winner:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

void Winner:: removeOptions(int a)
{
    
    if(options[a-1].first=="Talk to the lady")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Talk to the Bum")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Pick up Key" && madeFriend)
        options.erase(options.begin()+(a-1));
    
    
}

int Winner:: getVectorOption(int c)
{
    return options[c-1].second;
    
}



Space* Winner:: useAFriend(std:: vector<std::string>  a)
{
    
    int who;
    if(!a.empty())
    {
        cout << "Choose a friend to use: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "# " <<i+1<< a[i]<< endl;
        std:: cin >> who;
        
        if(a[who-1] == "Cedric")
            return lockSpace;
        else
            return self;
        
    }
    
    else
    {
        cout << "You have no friends." << endl;
        return self;
        
    }
    
    
    
}

Winner:: ~Winner()
{
    //cout << "destroying Winner." << endl;
    
}

