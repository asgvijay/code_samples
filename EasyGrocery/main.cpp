/**********************************
 * Author: Vijay Kumar
 * Date: 1/30/16
 * File: main.cpp
 * Project: Grocery List - Assignment 2
 * ********************************/


#include <iostream>
#include "List.hpp"
#include "Item.hpp"
#include <string>

using std:: cout;
using std:: endl;
using std:: cin;



int main()
{
    
    
    List grocery1;// create a list object
    std:: string name;//variable for user input
    std:: string unit;//variable for user input
    int amount;//variable for user input
    double price;//variable for user input
    bool i = true; //variable to run while loop
    char cont;// variable to check if user wants to continue
    Item* ptr;// pointer to create new item object
  
    
    cout << "Let's create a shopping list!" << endl;
    cout << "-----------------------------" << endl << endl;
    while (i)
        
    {
        cout << "What item would you like to add to the list?" << endl;
        getline(cin, name);
        cout << endl;
	cout << "What unit would you like to specify for the product? ie. (box, pound, ounces, etc.)" << endl;
        getline(cin, unit);
        cout << endl;
        cout << "What quantity would you like?" << endl;
        cin >> amount;
        cout<< endl;
        
    
        while(!cin.good() || amount <= 0)// user validation check
        {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a postive integer." << endl;
        cin >> amount;
        }
        cin.clear();
        cin.ignore(10000, '\n');
    
        cout << "What is the price per unit?" << endl;
        cin >> price;
        cout<< endl;
        while(!cin.good() || price<=0)
        {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a valid price." << endl;
        cin >> price;
        }
        
        cin.clear();
        cin.ignore(10000, '\n');
        
    
        ptr = new Item(name,unit,amount,price);//create new item object
        int count =0;// variable to check if item is the same as current item
        
        if(grocery1.getTotalItems()>0)//if there are items in the array
        {
            for(int j = 0; j<grocery1.getTotalItems(); j++)
            {
                if(*ptr == grocery1.getItem(j))//overloaded == operator to check if item is the same as one in array
                {
                    cout<< "This item already exists." << endl;
                    count++;
                }
            }
        }
        
        if(count==0)
            grocery1.addItem(ptr);//if item doesn not already exit, add product using addItem function
        else{
            delete ptr;//or delete the contents found at ptr
            ptr = NULL;
        }
    
            
        if(grocery1.getTotalItems()>=grocery1.getArraySize())// if the total Items is greater or equal to array size
            grocery1.expandList();//use expand list function to double the array size
    
    
        cout << "Would you like to add another item? Enter 'Y' or 'N'" << endl;
        cin >> cont;
        cout << endl << endl;
    
        if(toupper(cont) == 'N')
            i = false; // if user enter N change i to false so loops stops reiterating. 
        
        cin.clear();
        cin.ignore(10000, '\n');
       


    }
    
    
    
    grocery1.printList();// once add item loop is over, print the list using print list function
    

    return 0;
}


/*************************************************
 * overload operator for ==
 * compares the name variable of two items.
 * returns true if the variables are the same
 * ***********************************************/

bool operator==(Item LHS, Item RHS)
{
    
        return(LHS.name == RHS.name);

}

