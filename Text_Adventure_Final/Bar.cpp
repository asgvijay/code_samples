//
//  Bar.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Bar.hpp"
#include <iostream>

using std:: cout;
using std:: endl;

Bar:: Bar()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Lloyd Randall";
    keys = "kpyWSjVodSx0TVBXhV";
    spaceName = "City Bar";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
     options = { std::make_pair("Talk to bartender", 2), std:: make_pair("Talk to military guy",1), std:: make_pair("Check out what's in the safe",3),std:: make_pair("Go into the Street", 4), std::make_pair("Go into the Diner",5), std::make_pair("Go To the Library",6), std::make_pair("Go to the Airport.", 7), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12)  };
    
}
//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.

std:: string Bar:: beFriend()
{
    
    cout << "*******************TEAM*********************" << endl;
    cout << "You say hello to the bartender. He nods back, nonverbally opening communication. You tell him what you're setting out to do, hoping for an excited response. But you get nothing, only more longing stares. You wait for a few moments, then begin to think you're talking to the wrong person. Just as you get up from the stool, the bartender speaks up -- 'I was a professional fighter before it all went down. Same as my pop before me. I'd love to take down the Tower.'\n" << endl;
    cout << "Lloyd Randall has been added to your friend list.\n" << endl;
    madeFriend = true;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Bar:: badDecision()
{
    cout << "***********************OUCH**********************" << endl;
    cout << "You approach the military man, a brute of a man. He's mumbling to himself. But who doesn't mumble to themselves nowadays. You politely interrupt his inner dialogue and the man jerks out of his daymare and flings the table across the room. In a rage he grabs you by your hair and crushes his fist into your belly. You instantly crumble to the floor as the civil servant barrels through the bar door and out into the streets.\n" << endl;
    cout << "That took a lot out of you. You just lost 40 in your oxy level.\n" << endl;
    return 40;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Bar:: getKey()
{
    if(madeFriend)
    {
    cout << "You make your way behind the bar and peer in the open safe. The only thing left is a scrap of paper with 'kpyWSjVodSx0TVBXhV' written across it in red ink. Looks important. You jot down the code in your notebook.\n" << endl;
    return keys;
    }
    else
    {    cout << "The bartender eyes you suspiciously. Probably shouldn't go back there.\n" << endl;
        return " "; 
    }
}
//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.

Space* Bar:: moveOn(int a)
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

void Bar:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You walk through the swinging door and enter a bar pulled right out of a classic movie. Tacky neon lights, strangers using alcohol as a numbing agent and table tops as pillows. There's a single bartender behind a bar with only a couple bottles left on display. At this point in history, doesn't matter what's in the bottles as long as it kills reality for a bit. Might as well be gasoline.\n\nThe bartender cleans glasses staring into oblivion.  Behind the bar is an open safe with a single piece of paper in it. Across the bar is rather large military man still in uniform. He could be some good muscle to help with the mission.\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "This place oozes depression. And you definitely don't need any more of that.\n" << endl;
        
    }
    cout << "What would you like to do?\n" << endl;
    printOptions();

    
    
}

//This function prints the menu

void Bar:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " << options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void Bar:: removeOptions(int a)
{
    if(options[a-1].first=="Talk to bartender")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Talk to military guy")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Check out what's in the safe" && madeFriend)
        options.erase(options.begin()+(a-1));
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int Bar:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* Bar:: useAFriend(std:: vector<std::string>  a)
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
        cout << "You have no friends.\n" << endl;
        return self;
        
    }
    
    
    
}

Bar:: ~Bar()
{
 //cout << "destroying Bar." << endl;

    
}


