
//  Street.cpp
///  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Street.hpp"
#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Street:: Street()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "XZYvBisLXEr4aI/edit";
    spaceName = "City Streets";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std::make_pair("Talk to the lady", 1), std:: make_pair("Talk to the Bum",2), std:: make_pair("Check out the code on the bums hand",3),std:: make_pair("Go into the Bar", 4), std::make_pair("Go into the Diner",5), std::make_pair("Go Into the Library",6), std::make_pair("Go into the Airport.", 7), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12)  };
    
}

//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.

std:: string Street:: beFriend()
{
    cout << "*******************TEAM*********************" << endl;
    cout << "You approach the sleeping man and wake him, asking if he needs any help. He shivers in response, so you pull off your jacket and hand it to him. He thanks you and gets to his feet, as though your kindness not only lent warmth, but a resurgence of strength. You tell the man what your looking to accomplish, and he offers to help. Although, you're not sure how a man in his condition can help.\n" << endl;
    cout << "Joe Kipp has been added to your friend list.\n" << endl;
    madeFriend = true;
    return people;
    
    
}

//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level

int Street:: badDecision()
{
    cout << "***********************OUCH**********************" << endl;
    cout << "The old lady freaks out and the dog goes into security mode and bites you in the leg. I guess this is what happens when the city's leftovers are far from humane. Twenty points have been deducted from your Oxy Level.\n" << endl;
    return 20;
    
}

//This function returns the spaces key variable if the madefriend variable is true.

std::string Street:: getKey()
{
    
        if(madeFriend)
        {
            cout << "You lean in to check out the code on Joe's wrist. Joe tells you that he used to work for MT. Just as with every other employee of MT, his wrist was branded with a unique ID kpyWSjVodSx0TVBXhVXZY when he started. The brand on your wrist looks similar.\n" << endl;
            return keys;
        }
        else
        {    cout << "The bum smacks your hand and tells you to BACK OFF!\n" << endl;
            return " "; 
        }
    
}

//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.


Space* Street:: moveOn(int a)
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

void Street:: roomOptions()
{
    if(first)
    {
    cout << "***********************************************" << endl;
    cout << "             " <<getSpaceName()<< "            " << endl;
    cout << "***********************************************" << endl;
    cout << endl;
    cout << "You are in a seemingly deserted intersection of a desolate city. You notice a few dilapitaed businesses with hardly operational 'open' signs. The people running these places are what we call the cemented. No matter what's happening around them, they stick until they die. God Bless 'em.\n\nThe places still operational are a broken down bar, a boarded up library, a diner you wouldn't eat at even in the apocolypse and a fenced up airport across the way.\n\nLooming in the distance is the god forsaken Monarch Towers that used up all the life we had here in Lindenhurst.\n\nMaybe one of these places will have some strapping volunteers that will help me on my mission.\n\nAsk you walk the streets you notice a little old lady walking her dog -- maybe she shouldn't be out here at this hour? You also spy a homeless man lying in a pool of piss -- at least it seems that way. You notice he's wearing a tattered dress shirt with  military style stripes sewn on the shoulders. You see he's branded with a code across his wrist-- a code that every Monarch Towers slave gets the moment they start service. Maybe it means something.\n\nTime to make a decision." << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "The streets sing a song of the beaten. The Monarch Towers sure did a number on this place.\n" << endl;
    
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();
    
}

//This function prints the menu

void Street:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.


void Street:: removeOptions(int a)
{
    
    if(options[a-1].first=="Talk to the lady")
       options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Talk to the Bum")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Check out the code on the bums hand" && madeFriend)
        options.erase(options.begin()+(a-1));

    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int Street:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* Street:: useAFriend(std:: vector<std::string>  a)
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

Street:: ~Street()
{
    //cout << "destroying Street." << endl;
  
}


