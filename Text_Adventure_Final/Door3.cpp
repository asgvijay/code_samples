//
//  Door3.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Door3.hpp"
#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Door3:: Door3()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "1234";
    spaceName = "Door 3";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std:: make_pair("Back to the roof", 4), std::make_pair("Try Door 1",5), std::make_pair("Try Door 2",6), std::make_pair("Go For The MainFrame", 10), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12) };
    
}
//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.

std:: string Door3:: beFriend()
{
    
    cout << "You just made friends with Joe Kipp the Bum." << endl;
    cout << "Joe has been added to your friend list." << endl;
    madeFriend = true;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Door3:: badDecision()
{
    cout << "You just made a bad decision. Twenty points have been deducted from your Oxy Level." << endl;
    return 20;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Door3:: getKey()
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

Space* Door3:: moveOn(int a)
{
    if(a==4)
        return spaceName1;
    else if(a==5)
        return spaceName2;
    else if(a==6)
        return spaceName3;
    else
        return lockSpace;
    
}
//This function prints the options to the current space.
//If the space is visited for the first time, the intro is printed,
//if not, the shorter statement is printed.

void Door3:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "Door 3 opens easily. Maybe too easily. The room is dark and seems to be absent of any danger. You enter the a quiet room that leads to one doorway marked 'Main Frame.' As you walk towards the far door, your footsteps echoing off the bare walls, you here a man's voice, 'Stop right there.'\n\nYou turn to see a strapping guard step out of the dark corner of the room. You can't take him -- you think. Then another set of footsteps and another. Two more guards slowly step out of adjacent, dark corners. Each one as strapping as the next. Well, now you're probably a bit over your head.\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "The guards are waiting for you, ready for attack in the middle of the room.\n" << endl;
        
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();

    
}
//This function prints the menu

void Door3:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void Door3:: removeOptions(int a)
{
    
    if(options[a-1].first=="Talk to the lady")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Talk to the Bum")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Pick up Key")
        options.erase(options.begin()+(a-1));
    
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int Door3:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.


Space* Door3:: useAFriend(std:: vector<std::string>  a)
{
    cout << "Who would you like to send in there?\n" << endl;
    int who;
    if(!a.empty())
    {
        cout << "Choose someone: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "#" <<i+1<<" "<< a[i]<< endl;
        std:: cin >> who;
        
        if(a[who-1] == "Lloyd Randall")
        {
            cout << "Lloyd barrels his way into the room, and as if he's been waiting his whole like to do this, he manhandles all three of the oversized security guards as if they were evil little children.\n" << endl;
            return lockSpace;
        
        }
        else
        {   cout << "Oh no. " << a[who-1] << " is not equipped to handled this. He goes down for the count in an instant, and you have to drag him out of there, all while getting pelted on the back with police wands. Ouch. That's going to cost some oxygen points.\n" << endl;
            return self;
        }
    }
    
    else
    {
        cout << "You have no friends.\n" << endl;
        return self;
        
    }
    
    
    
}

Door3:: ~Door3()
{
  //cout << "destroying Door3." << endl;

    
}

