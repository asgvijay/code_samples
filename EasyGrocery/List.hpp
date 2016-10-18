/**********************************
 ** Author: Vijay Kumar
 ** Date: 1/30/16
 ** File: List.hpp
 ** Project: Grocery List - Assignment 2
 *********************************/

#ifndef List_hpp
#define List_hpp

#include "Item.hpp"

class List
{

private:
    Item** grList;
    int totalItems;
    int arraySize;
    Item** newStuff;
    
    
    
public:
    List();
    void addItem(Item* ptr);
    void expandList();
    void printList();
    void setTotalItems(int b);
    int getTotalItems();
    void setArraySize(int a);
    int getArraySize();
    friend bool operator==(Item LHS, Item RHS);
    Item getItem(int a);
    
    
};





#endif
