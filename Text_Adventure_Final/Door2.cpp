//
//  Door2.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Door2.hpp"

#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Door2:: Door2()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Joe Kipp";
    keys = "1234";
    spaceName = "Door 2";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std:: make_pair("Back to the roof", 4), std::make_pair("Try Door 1",5), std::make_pair("Try Door 3",6), std::make_pair("Go For The MainFrame", 10), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12) };
    
}

//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.


std:: string Door2:: beFriend()
{
    
    cout << "You just made friends with Joe Kipp the Bum." << endl;
    cout << "Joe has been added to your friend list." << endl;
    madeFriend = true;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Door2:: badDecision()
{
    cout << "You just made a bad decision. Twenty points have been deducted from your Oxy Level." << endl;
    return 20;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Door2:: getKey()
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

Space* Door2:: moveOn(int a)
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
void Door2:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "Door 2 is locked, but since the exodus you've become skilled and kicking locked doors down. Typically, the door has no need to be locked, since anything valuable behind it has been long gone. It feels empowering to knock down barriers with a swift kick. This time, however, you weren't expecting such a sight -- a group of cloaked men circled around a hologram projected in the center of the room.\n\nThe hologram is running autonomously, chanting in a dialect you haven't heard in ages, Old English.\n\nThe cloaked men seem to be in a trance, as the smashed doorway didn't cause them to blink. Through the circle and across the room, you see a door marked 'Main Frame.' That's where we need to go. But how should we get there?\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "The chanting continues in the creepiest setting you've seen since the tower set foot in this town.\n" << endl;
        
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();

    
}
//This function prints the menu

void Door2:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void Door2:: removeOptions(int a)
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

int Door2:: getVectorOption(int c)
{
    return options[c-1].second;
    
}


//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* Door2:: useAFriend(std:: vector<std::string>  a)
{
    cout << "Who would you like to send in there?\n" << endl;
    int who;
    if(!a.empty())
    {
        cout << "Choose someone: " << endl;
        for(int i = 0; i<a.size(); i++)
            cout << "#" <<i+1<< " " << a[i]<< endl;
        std:: cin >> who;
        
        if(a[who-1] == "Whitney")
        {   cout << "Whitney is up for the challenge. She begins to repeat a phrase in latin, and the men slowly turn their attention towards Whitney. She's hypnotizing them with her words, overriding anything the hologram was causing them to do.  With the distraction in place, you head for the Mainframe.\n" << endl;
            return lockSpace;
        }
        else
        {
            cout << a[who-1] << " slowly walks into the room hoping to not wake the hypnotized cloaked men. Just as you think all is going well, one quiet footstep awakens the group and they simultaneously attack. You have to fight them off of you to get out of harms way. That'll cost some energy points.\n";
            return self;
        }
    }
    
    else
    {
        cout << "You have no friends.\n" << endl;
        return self;
        
    }
    
}

Door2:: ~Door2()
{
   //cout << "destroying Door2." << endl;
   
}
