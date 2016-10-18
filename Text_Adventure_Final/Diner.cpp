//
//  Diner.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Diner.hpp"
#include <iostream>

using std:: cout;
using std:: endl;


Diner:: Diner()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Cedric Kahn";
    keys = "cument/d/1S_p68q25Zy5";
    spaceName = "City Diner";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
     options = { std::make_pair("Check out what he's doing on his phone", 3), std:: make_pair("Talk to the employee",2), std:: make_pair("Grab oxygen canister",1),std:: make_pair("Go into the Street", 4), std::make_pair("Go into the Bar",5), std::make_pair("Go To the Library",6), std::make_pair("Go to the Airport.", 7), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12)};
    
}
//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.


std:: string Diner:: beFriend()
{
    cout << "***********************TEAM**********************" << endl;
    cout << "Sometimes help is help, even if it's given from an asthmatic kid. You let him know about your mission and he excitedly listens. He joins without hesitation, admitting that he most likely won't be able to help, but that he's obsessed with Monarch Towers and has been trying to hack into their system for months -- using his mobile device. You find the irony amusing.  Impressionable kids today. You formally meet Cedric Kahn and he's been added to your team.\n" << endl;
    madeFriend = true;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Diner:: badDecision()
{
    cout << "***********************OUCH**********************" << endl;
    cout <<"You take a good amount of energy to stack tables on top of tables to reach the rafters above. But an oxy canister is a valuable find and can help the cause tremendously. You finally get your makeshift ladder tall enough to reach the canister with your fingertips. The moment it comes in your grasp you know it's empty. Damn, you took a risk and you lost. Going for the empty canister caused you to expell a ton of energy. You dropped 15 oxygen level points.\n" << endl;
    return 15;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Diner:: getKey()
{
    if(madeFriend)
    {cout <<"Cedric shifts to show the screen of his mobile device, a thin piece of glass that looks like it can fold tighlty and stored about anywhere. On the screen you see 'Monarch Towers Secure' along with the digits 'cument/d/1S_p68q25Zy5'. Cedric tells you he's been deciphering this code for a while and these numbers are as far as he's gotten. You store them in your notebook\n" << endl;
        return keys;
    }
    else
    {    cout << "The employee turns away and gives you a dirty look.\n" << endl;
        return " ";
    }
   
}
//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.

Space* Diner:: moveOn(int a)
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

void Diner:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You enter the Diner, the thick smell of grease makes you instantly hungry. Places like these only serve high-caloric foods nowadays. Everyone needs to eat for utility, so the bite with the most shit in it is usually the best. You examine the room and quickly eye an oxygen canister hanging from the ceiling rafters. An extra shot of oxy -- as we call it -- always makes the day better. Aside from that, the only other interesting part of this place is a lone employee, a lenky kid, working behind the counter. He's wide-eyed, staring at his mobile device. You also notice that he's severly short of oxgyen as he's wheezing strongly.\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "This place makes me hungry. What I wouldn't give for an actual cow-burger and potato fries.\n" << endl;
        
    }
    cout << "What would you like to do?\n " << endl;
    printOptions();

    
    
}
//This function prints the menu

void Diner:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " << options[i].first<< endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.


void  Diner:: removeOptions(int a)
{
    if(options[a-1].first=="Check out what he's doing on his phone" && madeFriend)
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Talk to the employee")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Grab oxygen canister")
        options.erase(options.begin()+(a-1));
    
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int Diner:: getVectorOption(int c)
{
    return options[c-1].second;
    
}


//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* Diner:: useAFriend(std:: vector<std::string>  a)
{
    
    int who;
    if(!a.empty())
    {
        cout << "Choose a friend to use: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "# " <<i+1<< a[i]<< endl;
        std::cin >> who;
        
        if(a[who-1] == "Cedric")
            return lockSpace;
        else
            return self;
        
    }
    
    else
    {
        cout << "You have no friends.\n" << endl;
        return self;
        
    }
    
    
    
}


Diner:: ~Diner()
{
  //cout << "destroying Diner." << endl;
    
}

