
/**********************************
 ** Author: Vijay Kumar
 ** Date: 1/30/16
 ** File: List.cpp
 ** Project: Grocery List - Assignment 2
 ** ********************************/


#include "List.hpp"
#include "Item.hpp"
#include <iostream>
#include <iomanip>

using std:: cout;
using std:: cin;
using std:: endl;
using std:: setw;


/*****************************************
 * Default constructor initializes the pointer
 * to point to an array of pointers to Item objects,
 * totalItems to 0 and arraysize to 4.
 * ******************************************/

List:: List()
{

    grList = new Item*[4];
    totalItems =0;
    arraySize = 4;
    
    
}

/*****************************************
 * addItem function takes a pointer to an Item as a
 * parameter. adds the item to the next spot
 * available in the array
 *******************************************/

void List:: addItem(Item* ptr)
{
    
    *(grList +totalItems)=ptr;
    
    totalItems++;
    
}


        
 /****************************************************
 * exapandList function doubles the size of the array.
 * creates a temp array twice the size of the original array,
 * populates the temp array with the contents of the original array.
 * arraySize is doubled, the original grList array is deleted
 * then a new grList is created, doubled in size, then all 
 * items are added to the original array.
 * ********************************************************/
        
void List:: expandList()
{
    

    newStuff = new Item*[totalItems*2];
        
    for(int k=0; k<totalItems; k++)
        *(newStuff +k) = *(grList+k);
    
    arraySize *=2;
    
    delete[]grList;
    
    grList = new Item*[totalItems*2];
    
    for(int i=0; i<totalItems; i++)
        *(grList +i) = *(newStuff+i);
    
    newStuff = NULL;
   
    
}

    
 /****************************************************
 * printList function prints the name, unit, qt and price
 * of each item. It calculates and prints the total item
 * price then adds all the items together to print 
 * the total price.
 * ****************************************************/

void List:: printList()
{
    double total = 0.00;
    
    for(int i=0; i < totalItems; i++)
    {   cout << setw(40)<< std::left << "Item" << setw(8) << std:: left << "Unit" << setw(8) << std::left<< "Qt." << setw(9) << std:: left<< "Price" << setw(8) << std:: left<< "Total" << endl;
        
        cout << setw(40)<< std::left << (*(grList+i))->getName() << setw(8) << std:: left << (*(grList+i))->getUnit() << setw(8)<< std::left <<(*(grList+i))->getQt() << "$"<< setw(8)<< std::left << std:: setprecision(8)<<(*(grList+i))->getPrice() << "$" <<setw(8) << std:: left << std:: setprecision(8)<<(*(grList+i))->getTotalPrice()<< endl << endl;
        
        total+= (*(grList+i))->getTotalPrice();
    
    }
    
    cout << "The total cost for this list is: " << "                                $" << std:: setprecision(8)<< total << endl << endl;
    
    }

/*******************************************************
 * setArraySize function uses an integer parameter to
 * set the arraySize variable.
 * *************************************************/



void List:: setArraySize(int a)
{
    
    arraySize=a;
    
}

/******************************************************
 * getArraySize returns the arraySize
 * **********************************************/
int List:: getArraySize()
{
    
    return arraySize;
}


/*****************************************************
 * setTotalItems function takes an integer parameter
 * to set the totalItems variable.
 * **************************************************/
void List:: setTotalItems(int b)
{
    
    totalItems=b;
    
}


/******************************************************
 * getTotalItems returns the totalItems variable
 * **********************************************/
int List:: getTotalItems()
{
    
    return totalItems;
    
}


/********************************************************
 * getItem function takes an integer parameter and
 * returns an Item. the integer is used to find the 
 * address in memory or the next item in the array.
 * ****************************************************/
Item List:: getItem(int a){
    
    return *(*(grList +a));
    
  
}


