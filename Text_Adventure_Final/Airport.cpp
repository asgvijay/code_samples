//
//  Airport.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Airport.hpp"
#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Airport:: Airport()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "https://docs.go";
    spaceName = "City Airports";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    options = { std::make_pair("Grab the Oxygen Tank", 1), std:: make_pair("Take note of the grafitti",3),std:: make_pair("Go into the Streets", 4), std::make_pair("Go into the Bar",5), std::make_pair("Go Into the Library",6), std::make_pair("Fly to the Monarch Towers.", 10), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12) };
    
}

//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.


std:: string Airport:: beFriend()
{
    
    cout << "Meet Joe" << endl;
    cout << "Joe has been added to your friend list." << endl;
    madeFriend = true;
    return people;
    
    
}

//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Airport:: badDecision()
{   cout << "***********************YES**********************" << endl;
    cout << "Holy Crap! This one is full! You just upped your oxygen level by 40.\n" << endl;
    return -40; // negative number will increase oxy level
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Airport:: getKey()
{
    
        cout << "You notice a beat up ladder leading to a perch atop the terminal building. That'll give you a close enough look at the grafitti. When you get up there, you notice a 'https://docs.go'. You know what this could be leading to. It's been stored in your notebook.\n" << endl;
        return keys;
    
}
//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.

Space* Airport:: moveOn(int a)
{
    if(a==4)
        return spaceName1;
    else if(a==5)
        return spaceName2;
    else if(a==6)
        return spaceName3;
    else
    {   
        return lockSpace;
    }
}
//This function prints the options to the current space.
//If the space is visited for the first time, the intro is printed,
//if not, the shorter statement is printed.
void Airport:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You enter the airport through a hole cut in the metal fencing. Seems like it's a route for many unauthorized visitors. But does anyone care about 'authorization' nowadays? Probably not.\n\nYou examine the surroundings. A small tarmac that needs a good weeding, a single terminal building and a lone helicopter that seems like it hasn't been used in decades.\n\nAbove the terminal building looms a Monarch Tower billboard. The propaganda that got idiot constinuents to put them into power in the first place. Spraypainted across the face of the billboard is a series of numbers, but you can't make it out from down here.\n\nYou spot an oxygen canister beneath a sewage grate. Probably left behind from the bums that used to live down there. It would take some energy to get the grate up and grab the canister. Oh the desicions."  << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You never become desensitized to the stench of urine hovering at nose height all throughout the airport.\n" << endl;
        
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();
    
}

//This function prints the menu

void Airport:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void Airport:: removeOptions(int a)
{
    
    if(options[a-1].first=="Grab the Oxygen Tank")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Take note of the grafitti")
        options.erase(options.begin()+(a-1));
    
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int Airport:: getVectorOption(int c)
{
    return options[c-1].second;
    
}


//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* Airport:: useAFriend(std:: vector<std::string>  a)
{
    cout << "Who would you like to fly the helicopter?" << endl;
    int who;
    if(!a.empty())
    {
        cout << "Choose someone: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "#" <<i+1<< " " << a[i]<< endl;
        std:: cin >> who;
        
        if(a[who-1] == "Joe Kipp")
        {
            cout<< "Joe awkwardly takes the pilot's seat and the team climbs in. He starts the chopper and the blades begin to spin, faster and faster. Just as the chopper is about to take off, you lean over to him and say, 'You sure you good to fly this thing?' He replies with a belch full of apocolyptic odors." << endl;
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


Airport:: ~Airport()
{
    //cout << "destroying Airport." << endl;
 
    
}

