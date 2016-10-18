/**********************************
 ** Author: Vijay Kumar
 ** Date: 1/30/16
 ** File: Item.hpp
 ** Project: Grocery List - Assignment 2
 *********************************/

#ifndef Item_hpp
#define Item_hpp
#include <string>

class Item
{
private:
    std:: string name;
    std:: string unit;
    int quantity;
    double price;
    
public:
    Item(std:: string name, std:: string unit, int quantity, double price);
    void setName(std:: string name);
    std:: string getName();
    void setUnit(std:: string unit);
    std:: string getUnit();
    void setQt(int a);
    int getQt();
    void setPrice(double b);
    double getPrice();
    double getTotalPrice();
    friend bool operator==(Item LHS, Item RHS);
    
};





#endif
