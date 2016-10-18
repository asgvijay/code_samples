//
//  MainFrame.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "MainFrame.hpp"


#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



MainFrame:: MainFrame()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "1234";
    spaceName = "Main Frame";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std:: make_pair("Back to the Roof", 4), std::make_pair("Try to hack into the system",11), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12) };
    
}
//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.


std:: string MainFrame:: beFriend()
{
    
    cout << "N/A" << endl;
    cout << "N/A" << endl;
    madeFriend = true;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int MainFrame:: badDecision()
{
    cout << "N/A" << endl;
    return 20;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string MainFrame:: getKey()
{
    
    if(madeFriend)
    {
        cout << "N/A" << endl;
        return keys;
    }
    else
    {    cout << "N/A" << endl;
        return " ";
    }
    
}
//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.

Space* MainFrame:: moveOn(int a)
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

void MainFrame:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You made it. And with just a bit of oxy left. In the center of the room is the Main Frame computer -- the computer that holds all the code you wrote that put Monarch Towers on the map, and everyone else off the map. All you need to do is login, and you can set a course correction. Can reparations ever truly be made?\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "There it is -- the Main Frame computer.\n" << endl;
        
    }
    cout << "What would you like to do?\n " << endl;
    printOptions();

    
}

//This function prints the menu

void MainFrame:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void MainFrame:: removeOptions(int a)
{
    
    if(options[a-1].first=="N/A")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="N/A")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="N/A")
        options.erase(options.begin()+(a-1));
    
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int MainFrame:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* MainFrame:: useAFriend(std:: vector<std::string>  a)
{
    cout << "You're sitting it front of the computer -- the portal to control the oxygen flow. All you have to do is login and you'll be able to reverse the flow of oxygen. But what's the password. Maybe your notes can give you a clue:\n " << endl;
    
    if(!a.empty())
    {
        cout << "Here are your list of notes:\n " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "# "<< i+1<< " " << a[i]<< endl;
        cout << endl;

    }
    cout << "You hit enter on the screen and you see the login screen. What should you enter:\n " << endl;
    cout << "#1: Atanasoff" << endl;
    cout << "#2: Knuth" << endl;
    cout << "#3: Pascal" << endl;
    cout << "#4: Turing" << endl;
    cout << "#5: Bartik" << endl;
    
    int choice;
    std:: cin >> choice;
    
    if (choice ==4)
        return lockSpace;
    
    else
    {
        cout << "Oh no. You've been locked out of the computer. That's going to cost some energy. Hopefully, we have enough oxygen to last.\n " << endl;
        return self;
        
    }
    
    
    
}


MainFrame:: ~MainFrame()
{
  //cout << "destroying Mainframe." << endl;
    
}

