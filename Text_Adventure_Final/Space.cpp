//
//  Space.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Space.hpp"
#include <iostream>
using std:: cout;
using std:: endl;

Space:: Space()
{
    
    
}

Space:: ~Space()
{
    
    //cout << "destroying space." << endl;
    
}


void Space::setSpace(Space* a, Space* b, Space *c, Space* d, Space* e)
{
    spaceName1 =a;
    spaceName2 =b;
    spaceName3=c;
    spaceName4 = d;
    lockSpace=d;
    
    self = e;
    
    first = true;
}

Space* Space:: moveOn(int a)
{
    if(a==4)
        return spaceName1;
    else if(a==5)
        return spaceName2;
    else if(a==6)
        return spaceName3;
    else if(a==7)
        return lockSpace;
    else
    {   cout << "Can't go there." << endl;
        return self;
    }
}

std:: string Space:: getSpaceName()
{
    
    return spaceName;
}


Space* Space:: useAFriend(std:: vector<std::string>  a)
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
        cout << "You have no friends." << endl;
        return self;
        
    }
    
    
    
}

