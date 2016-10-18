/**********************************************
 **** Program Filename: print.cpp
 **** Author: Vijay Kumar
 **** Date: 1/11/16
 **** Description: Conway's Game of Life
 ***************************************************/
#include "print.hpp"
#include<iostream>

using std:: cout;
using std:: endl;

/************************
 * This function prints out the visible portion of our gameboard.
 * We have a 2 cell border, so the printing begins at i=2 and ends at row or col -2
 * *************************/


void print(int *gameBoard, int  row, int  col)
{
    
   
    for(int i=2; i<row-2; i++)
    {   for(int j=2; j<col-2; j++)
        {   std:: cout  << gameBoard[i*col+j] << " " ;
            
        }
        std:: cout << std:: endl;
    
    }
    
    
  
    
}

