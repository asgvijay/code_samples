//
//  MonarchTowers.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "MonarchTowers.hpp"

#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



MonarchTowers:: MonarchTowers()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "1234";
    spaceName = "Monarch Towers";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std:: make_pair("Door 1", 4), std::make_pair("Door 2",5), std::make_pair("Door 3",6), std::make_pair("Back to the Airport ",10),std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12) };
    
}

//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.


std:: string MonarchTowers:: beFriend()
{
    
    cout << "You just made friends with Joe Kipp the Bum." << endl;
    cout << "Joe has been added to your friend list." << endl;
    madeFriend = true;
    return people;
    
    
}

//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int MonarchTowers:: badDecision()
{
    cout << "You just made a bad decision. Twenty points have been deducted from your Oxy Level." << endl;
    return 20;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string MonarchTowers:: getKey()
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
//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.

Space* MonarchTowers:: moveOn(int a)
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

//This function prints the options to the current space.
//If the space is visited for the first time, the intro is printed,
//if not, the shorter statement is printed.
void MonarchTowers:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "Thank god! You made it to the rooftop of Monarch Towers. Even though Joe had the mark of a pilot seen in those shoulder stripes, he must not have been in the pilot's seat for a while. But nevertheless, he got you here, and that means everything. You're not looking forward to the trip back down... if there is one.\n\nNow that you've got your feet planted on the roof's solid surface, you take in your surroundings. You see 3 Doors. You're not sure where they lead, but when has not knowing ever stopped you before?\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "It's cold as hell up here on the roof of Monarch Towers.\n" << endl;
        
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();
    
}
//This function prints the menu

void MonarchTowers:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void MonarchTowers:: removeOptions(int a)
{
    
    if(options[a-1].first=="")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="")
        options.erase(options.begin()+(a-1));
    
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int MonarchTowers:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* MonarchTowers:: useAFriend(std:: vector<std::string>  a)
{
    cout << "Who would you like to fly the helicopter?\n" << endl;
    int who;
    if(!a.empty())
    {
        cout << "Choose someone: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "#" <<i+1<< " "<< a[i]<< endl;
        std:: cin >> who;
        
        if(a[who-1] == "Joe Kipp")
        {   cout << "Joe got us up here okay. Hopefully he can get us back down in one piece.\n" << endl;
            return lockSpace;
        }
        else
        {   cout << "Oh no!!!!! " << a[who-1] << " doesn't know how to fly!!!! Before the helicopter gets ten feet off the ground it crashes back down to the tarmac. That hurt pretty bad!\n" << endl;
            return self;
        }
    }
    
    else
    {
        cout << "You have no friends.\n" << endl;
        return self;
        
    }
    
    
    
}

MonarchTowers:: ~MonarchTowers()
{
  // cout << "destroying Monarch." << endl;
 
}

