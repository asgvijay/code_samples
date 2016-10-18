//
//  Door1.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Door1.hpp"
#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Door1:: Door1()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
  madeFriend= false;
    people = "Joe Kipp";
    keys = "1234";
    spaceName = "Door 1";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std:: make_pair("Back to the Roof", 4), std::make_pair("Try Door 2",5), std::make_pair("Try Door 3",6), std::make_pair("Go For The MainFrame", 10), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12) };
    
}
//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.



std:: string Door1:: beFriend()
{
    
    cout << "You just made friends with Joe Kipp the Bum." << endl;
    cout << "Joe has been added to your friend list." << endl;
    madeFriend = true;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Door1:: badDecision()
{
    cout << "You just made a bad decision. Twenty points have been deducted from your Oxy Level." << endl;
    return 20;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Door1:: getKey()
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

Space* Door1:: moveOn(int a)
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

void Door1:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You enter Door 1 to find yourself in a lounge of sleeping men and women. You're not sure why they are all passed out until you see vents in the walls actively spewing gas into the room. Is it some sort of gas chamber? Are these people dead? You notice an oxygen guage on the far wall that reads the air purity in the room. They must all be high! Getting stoned on the oxygen we all need to survive. Those bastards!\n\nAlong the far wall you notice a door. Above it -- a sign that reads 'Main Frame.' It's exactly where you want to go.\n\nBut the level of oxygen in the room could get you just as stoned as the rest, so you think twice about heading for the far door." << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "Getting a deep breath of pure oxygen sure sounds great, but where would it leave the mission?\n" << endl;
        
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();
    
}

//This function prints the menu

void Door1:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void Door1:: removeOptions(int a)
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

int Door1:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

void Door1::killFloor()
{
    
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.


Space* Door1:: useAFriend(std:: vector<std::string>  a)
{
    cout << "Who would you like to send in there?\n" << endl;
    int who;
    if(!a.empty())
    {
        cout << "Choose someone: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "#" <<i+1<< " "<<a[i]<< endl;
        std:: cin >> who;
        
        if(a[who-1] == "Cedric Kahn")
        {
            cout << "Cedric tiptoes into the room and stops shortly after entering. He slowly turns back to the door. He has a terrified look upon him. He stumbles to find his words, then delivers, 'I can BREATHE!' Cedric's asthma must allow just the right amount of oxygen into his blood for him to not get stoned. We're in luck!!!" << endl;
            return lockSpace;
            
            
        }
        else
        {   cout << a[who-1] << " seems to be getting really sleepy in there.\n" << endl;
            cout << "Uh oh. Not going to make it. Get out of there! That cost you a bit of oxygen!.\n" << endl;
            return self;
        }
    }
    
    else
    {
        cout << "You have no friends.\n" << endl;
        return self;
        
    }
    
    
    
}

Door1:: ~Door1()
{
//    cout << "destroying Door1." << endl;

}

