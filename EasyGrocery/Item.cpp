

/**********************************
 ** Author: Vijay Kumar
 ** Date: 1/30/16
 ** File: Item.cpp
 ** Project: Grocery List - Assignment 2
 ** ********************************/

#include "Item.hpp"
#include <string>

/******************************************************
 * Constructor takes 4 parameters to set the values of
 * all member variables of the class.
 * Uses the classes set functions to set vars.
 * ****************************************************/

Item:: Item(std:: string name, std:: string unit, int quantity, double price)
{
    setName(name);
    setUnit(unit);
    setQt(quantity);
    setPrice(price);
    
}

/**********************************************
 * setName function uses a string variable
 * to set the name variable.
 * *****************************************/
void Item:: setName(std:: string name)
{
    this->name=name;
    
}


/*********************************************
 * getName returns the name variable
 * ****************************************/
std::string Item::getName()
{
    
    return name;
    
}

/*********************************************
 * setUnit function takes a string parameter
 * to set the unit variable.
 * ******************************************/
void  Item::setUnit(std:: string unit)
{
  
    this->unit=unit;
    
}


/***********************************************
 * getUnit function returns the unit variable.
 * *******************************************/
std:: string Item::getUnit()
{
    
    return unit;
    
}


/**********************************************
 * setQt function takes an integer parameter
 * to set the quantity.
 * *************************************/
void Item:: setQt(int a)
{
 
    quantity = a;
    
}
/******************************************
 * getQt function returns the quantity var.
 * *****************************************/
int Item:: getQt()
{
    
    return quantity;
    
}

/******************************************
 * setPrice function takes a double 
 * parameter to set the price var.
 * ***************************************/

void Item:: setPrice(double b)
{
    
    price = b;
    
}

/******************************************
 * getPrice function returns the price var.
 * *****************************************/
double Item:: getPrice()
{
    
    return price;
}


/*********************************************
 * getTotalPrice function multiplies the quanity
 * by price variable and returns the result.
 * ********************************************/
double Item:: getTotalPrice()
{
    
    return (price*quantity);
    
}
