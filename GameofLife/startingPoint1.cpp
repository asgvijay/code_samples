/**********************************************
 **** Program Filename: startingPoint1.cpp
 **** Author: Vijay Kumar
 **** Date: 1/11/16
 **** Description: Conway's Game of Life
 ***************************************************/

#include "startingPoint.hpp"
#include <iostream>

using std:: cout;
using std:: cin;
using std:: endl;

/*******************************************************
 * This function creates a starting shape
 * and starting place for the shape within the
 * gameboard. The user chooses the shape and the 
 * cell in which to start the shape. Based on
 * the user's choices, the function populates the gameboard
 * with the necessary live cells.
 * ******************************************************/

void startingPoint(int* ptr, int col)
{
    
    
    
    int select; //this marks the selection of the shape
    int startRow;// this marks the user selection starting row
    int startCol;// this marks the user selected starting col.

    std:: cout << "Which pattern do you want to start with?" << std:: endl;
    std:: cout << std:: endl;
    std:: cout << endl;
    std:: cout << "#1 - A Blinker: Oscillator" << std:: endl;
    std:: cout << endl;
    std:: cout << "#2 - A Glider" << std:: endl;
    std:: cout << endl;
    std:: cout << "#3 - A Glider Gun" << std:: endl;
    std:: cout << endl;
    std:: cout << "Please enter 1, 2 or 3." << std:: endl; 
    std:: cout << std:: endl; 
    std:: cin >> select;
    std:: cin.clear();
    std:: cin.ignore(10000, '\n');

	while (select < 1 || select > 3)//validate user input
    	{   	std:: cout << "Please enter 1, 2 or 3" << std:: endl;
        	std::cin >> select;
		std:: cin.clear();
        	std:: cin.ignore(10000, '\n');    
	}
    
    std:: cout << "Great! Now let's choose where to start your shape." << std:: endl;
    
    if (select ==1) // if user chooses shape 1
    {   std:: cout<< "Please choose a row between 1 and 40." << std:: endl;
        std:: cin >> startRow;
        std:: cin.clear();
    	std:: cin.ignore(10000, '\n');
	std:: cout << "Please choose a column between 4 and 15." << std:: endl;
        std:: cin >> startCol;
   	std:: cin.clear();
    	std:: cin.ignore(10000, '\n');
	while(startRow >40 || startRow < 1)// validate user input
	{
                std:: cout << "We need a row between 1 and 40. Let's try again." << std:: endl;
                std:: cout << "Which row would you like? Choose between 1 and 40." <<std:: endl;
                std:: cin >> startRow;
        	std:: cin.clear();
    		std:: cin.ignore(10000, '\n');
	}
        while(startCol<4 || startCol>15)
        {       std:: cout << "We need a column  between 4 and 15. Let's try again." << std:: endl;
                std:: cout << "Which column  would you like? Choose between 4 and 15." <<std:: endl;
                std:: cin >> startCol;
        	std:: cin.clear();
    		std:: cin.ignore(10000, '\n');

        } 



   }
    if (select ==2)//if user chooses shape 2
    {   std:: cout<< "Please choose a row between 2 and 38." << std:: endl;
        std:: cin >> startRow;
        std:: cin.clear();
    	std:: cin.ignore(10000, '\n');
	std:: cout << "Please choose a column between 2 and 18." << std:: endl;
        std:: cin >> startCol;
    	std:: cin.clear();
    	std:: cin.ignore(10000, '\n');
	while(startRow >38 || startRow < 2)//validate user input
	{
                std:: cout << "We need a row between 2 and 38. Let's try again." << std:: endl;
                std:: cout << "Which row would you like? Choose between 2 and 38." <<std:: endl;
                std:: cin >> startRow;
        	std:: cin.clear();
    		std:: cin.ignore(10000, '\n');
	}
        while(startCol<2 || startCol>18)
        {       std:: cout << "We need a column  between 2 and 18. Let's try again." << std:: endl;
                std:: cout << "Which column would you like? Choose between 2 and 18." <<std:: endl;
                std:: cin >> startCol;
        	std:: cin.clear();
    		std:: cin.ignore(10000, '\n');

        }



    }
    
    if (select ==3)//if user chooses shape 3
    {   std:: cout<< "Please choose a row between 1 and 3." << std:: endl;
        std:: cin >> startRow;
        std:: cin.clear();
    	std:: cin.ignore(10000, '\n');
	std:: cout << "Please choose a column between 4 and 15." << std:: endl;
        std:: cin >> startCol;
	std:: cin.clear();
    	std:: cin.ignore(10000, '\n');
	while(startRow >3 || startRow < 1)//validate user input
	{
		std:: cout << "We need a row between 1 and 3. Let's try again." << std:: endl;
		std:: cout << "Which row would you like? Choose between 1 and 3." <<std:: endl;
   		std:: cin >> startRow;
		std:: cin.clear();
    		std:: cin.ignore(10000, '\n');
	}
	while(startCol<4 || startCol>15)
	{	std:: cout << "We need a column  between 4 and 15. Let's try again." << std:: endl;
                std:: cout << "Which column  would you like? Choose between 4 and 15."<<std:: endl;
                std:: cin >> startCol;
		std:: cin.clear();
   		std:: cin.ignore(10000, '\n');	

	}

    }

 
    
    if (select == 1)//places shape 1 in the gameboard
    {
   	ptr[col*startRow+startCol]=1;
        ptr[col*startRow+(startCol+1)]=1;
        ptr[col*startRow+(startCol+2)]=1;
    }
    else if (select == 2)//places shape 2 in the gameboard
    {
 	ptr[col*startRow+startCol]=1;
        ptr[col*(startRow+2)+(startCol-1)]=1;
        ptr[col*(startRow+2)+startCol]=1;
        ptr[col*(startRow+2)+(startCol+1)]=1;
        ptr[col*(startRow+1)+(startCol+1)]=1;
    }
    
    else if (select == 3)//places shape 3 in the gameboard
    {
	ptr[col*startRow+startCol]=1;
        ptr[col*startRow+(startCol+1)]=1;
        ptr[col*(startRow+1)+startCol]=1;
        ptr[col*(startRow+1)+(startCol+1)]=1;
        ptr[col*(startRow+11)+(startCol-2)]=1;
        ptr[col*(startRow+11)+(startCol-1)]=1;
        ptr[col*(startRow+11)+(startCol+3)]=1;
        ptr[col*(startRow+11)+(startCol+4)]=1;
        ptr[col*(startRow+13)+(startCol-1)]=1;
        ptr[col*(startRow+13)+(startCol+3)]=1;
        ptr[col*(startRow+14)+startCol]=1;
        ptr[col*(startRow+14)+(startCol+1)]=1;
        ptr[col*(startRow+14)+(startCol+2)]=1;
        ptr[col*(startRow+15)+startCol]=1;
        ptr[col*(startRow+15)+(startCol+1)]=1;
        ptr[col*(startRow+15) +(startCol+2)]=1;
        ptr[col*(startRow+18)+(startCol+3)]=1;
        ptr[col*(startRow+19)+(startCol+2)]=1;
        ptr[col*(startRow+19)+(startCol+3)]=1;
        ptr[col*(startRow+19)+(startCol+4)]=1;
        ptr[col*(startRow+20)+(startCol+1)]=1;
        ptr[col*(startRow+20)+(startCol+5)]=1;
        ptr[col*(startRow+21)+(startCol+3)]=1;
        ptr[col*(startRow+22)+startCol]=1;
        ptr[col*(startRow+22)+(startCol+6)]=1;
        ptr[col*(startRow+23)+startCol]=1;
        ptr[col*(startRow+23)+(startCol+6)]=1;
        ptr[col*(startRow+24)+(startCol+1)]=1;
        ptr[col*(startRow+24)+(startCol+5)]=1;
        ptr[col*(startRow+25)+(startCol+2)]=1;
        ptr[col*(startRow+25)+(startCol+3)]=1;
        ptr[col*(startRow+25)+(startCol+4)]=1;
        ptr[col*(startRow+34)+(startCol+2)]=1;
        ptr[col*(startRow+34)+(startCol+3)]=1;
        ptr[col*(startRow+35)+(startCol+2)]=1;
        ptr[col*(startRow+35)+(startCol+3)]=1;
	}
}	
