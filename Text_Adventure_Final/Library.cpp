//
//  Library.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Library.hpp"
#include <iostream>
#include <vector>
using std:: cout;
using std:: endl;
using std:: cin;



Library:: Library()
{
    spaceName1 = NULL;
    spaceName2 = NULL;
    spaceName3 = NULL;
    spaceName4 = NULL;
    lockSpace = NULL;
    
    madeFriend= false;
    people = "Whitney";
    keys = "ogle.com/do";
    spaceName = "Deserted Library";
    
    //The options vector is a vector of pairs, a string and an int. The int is a tag for each menu option. The tag
    //is used to associate each menu option with a specific function in the game. ie "10" tag is to tell the program the user
    //is attempting to access a locked space. If the user picks a menu option with the "1" tag, the badDecision() will run.
    // Tags: 1 = badDecision(); 2 = beFriend(); 3 = getKey(); 4 = moveOn(); 5 = moveOn(); 6 = moveOn(); 7 = moveOn(); 8 =
    //printFriends(); 9 = printKeys(); 10 = useAFriend(), accessing Locked Space; 11 = useAFriend(), accessing winners circle
    
    options = { std::make_pair("Talk to the Librarian", 2), std:: make_pair("Help the little boy",1), std:: make_pair("Look through the stacks",3),std:: make_pair("Go into the Streets", 4), std::make_pair("Go into the Bar",5), std::make_pair("Go Into the Diner",6), std::make_pair("Go into the Airport.", 7), std::make_pair("See your list of friends", 8), std::make_pair("See your notes", 9), std::make_pair("Exit Game", 12)  };
    
}
//This function adds a friend to the user's vector of friends.
//it will adjust the madefriend value to true.


std:: string Library:: beFriend()
{
    cout << "***********************LET'S GO**********************" << endl;
    cout << "You'd gladly chat up this librarian in most cases, but asking one to join your bad-ass team of Monarch Towers burglars seems off. Why would a lovely lady like this ever get involved. That being said, you still need a 'Team,' whatever that may be. So you give her the mission elevator pitch, and before you can finish, she jumps up from her chair, grabs her jacket and spouts off a line in what seems to be French... but you're not confident in your foreign language deciphering skills. You eye her dumbly and she quickly responds in english, 'Oh sorry, sometimes it's hard to jump from one language to the next. I was saying that I'd love to help. It would be lovely to stop those piece of shi!t m@ther f*ckers.' The cursing shocks you and she sees it. 'I don't apologize for any language. It's all beautiful.'\n" << endl;
    cout << "Whitney has been added to your friend list.\n" << endl;
    return people;
    
    
}
//This function can effect the players oxygen level. It returns a specific int which then adjusts the
//players oxy level
int Library:: badDecision()
{   cout << "***********************KINDNESS**********************" << endl;
    cout << "You approach the little boy and notice he's wheezing considerably. You need to help him. You generously give hime 20 units of your oxy. He instantly perks to life and smiles.\n " << endl;
    madeFriend = true;
    return 20;
    
}
//This function returns the spaces key variable if the madefriend variable is true.
std::string Library:: getKey()
{
    
    if(madeFriend)
    {
        cout << "You eye the aisle of research on Monarch Towers. You assume all this information would be helpful, but it'd take years to go through it all. Like finding a needle in a haystack. As you peer down the long aisle, you feel a tug on your shirt. It's the little boy. He hands you a manila folder. You curiously open it to find a code in red ink 'ogle.com/do.' What's with all this red ink. You jot down the code in your notebook.\n" << endl;
        return keys;
    }
    else
    {    cout << "The rows of books are endless. It would take years to find anything relative.\n" << endl;
        return " ";
    }
    
}
//This function returns a pointer to the selected space.
//It uses the integer argument to reference the correct pointer
//to return.

Space* Library:: moveOn(int a)
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

void Library:: roomOptions()
{
    if(first)
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "You enter the library and the first thing you notice is this place looks like it hasn't been touched by despair. It's just like you remember libraries, even though you haven't been in one for decades before the Monarch Towers came to town. To be honest, you didn't even know they still existed. But this one -- wow. It was just amazing. Clean, smell of books, there's even a kid sitting in the corner with a book in hand.\n\nNear the entrance is a young woman. She smiles at you from over her book, then quickly gets back to business.\n\nYou clear your throat to get the Librarian's attention. She looks up and you silenty gesture over to the kid in the corner. You're wondering what the deal with the kid is. She tells you he's on his last canister of oxygen, and he wanted to spend his last moments with his 'happy' book friends.\n\nWhat a shame.\n\nOther than the two in the library, you notice an aisle of books on Monarch Towers. There could be some good info in there.\n" << endl;
        first = false;
    }
    else
    {
        cout << "***********************************************" << endl;
        cout << "             " <<getSpaceName()<< "            " << endl;
        cout << "***********************************************" << endl;
        cout << endl;
        cout << "Being in this library makes you never want to leave.\n" << endl;
        
    }
    cout << "What would you like to do? " << endl;
    printOptions();

    
}
//This function prints the menu

void Library:: printOptions()
{
    
    for(int i=0; i<options.size(); i++)
        cout << "# " << i+1 << " " <<options[i].first << endl;
    
}

//This function removes any option in the menu that
//cannot be used twice. It takes an integer as an option
//and references the string value in the options vector.

void Library:: removeOptions(int a)
{
    
    if(options[a-1].first=="Talk to the Librarian")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Help the little boy")
        options.erase(options.begin()+(a-1));
    
    else if(options[a-1].first=="Look through the stacks" && madeFriend)
        options.erase(options.begin()+(a-1));
    
    
}

//This function takes an integer as an argument and
//returns the int tag that is associated with each menu
//option.

int Library:: getVectorOption(int c)
{
    return options[c-1].second;
    
}

//This function takes a vector of strings as an argument.
//It prints the string then allows the user to choose an
//option from the vector. If the user chooses the correct
//option, a pointer to the locked room is returned, if not,
//the pointer to the current space is returned.

Space* Library:: useAFriend(std:: vector<std::string>  a)
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


Library:: ~Library()
{
  //cout << "destroying Library." << endl;
    
}

