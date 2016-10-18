//
//  main.cpp
//  overload operator
//
//  Created by Vijay Kumar on 1/29/16.
//  Copyright © 2016 Vijay Kumar. All rights reserved.
//

#include <iostream>

using std:: cout;
using std:: endl;

class Item
{
    
private:
    int val;
    
public:
    Item(int a);
    Item ();
    friend bool operator==(Item a, Item b);
    
};



Item::Item()
{
    
    val = 0;
    
}

Item:: Item(int a)
{
    
    this->val = a;
    
}


bool operator==(Item a, Item b)
{
    
    return a.val == b.val;
    
}

int main() {
    
    
    
    Item a;
    Item b(6);
    
    if(a == b)
        cout << "Item a and Item b are equal" << endl;
    else
        cout << "Item a and Item b are not equal." << endl;
    
    
    return 0;
}
