/**********************************************
 *** Program Filename: main.cpp
 *** Author: Vijay Kumar
 *** Date: 1/11/16
 *** Description: Conway's Game of Life
 **************************************************/

#include <iostream>
#include "startingPoint.hpp"
#include "deadAlive.hpp"
#include "print.hpp"
#include <cstdlib>

int main()
{
    int const ROWS =44;//row variable
    int const COLS = 24;// col variable
    int gens =0;//counter for generations
   
    
    int gameBoard1[ROWS][COLS];//creating first gameboard
    int gameBoard2[ROWS][COLS];// creating second gameboard
    
    int *ptrGame1;
    int *ptrGame2;
    
    ptrGame1 = &gameBoard1[0][0];//point to first address in gameboard 1
    ptrGame2 = &gameBoard2[0][0];//point to first address in gameboard 2
    
    for(int i = 0; i<ROWS; i++)// intialize gameboard to 0
    {   for(int j=0; j<COLS; j++)
            gameBoard1[i][j]=0;
    }
    
    for(int i = 0; i<ROWS; i++)// initialize gameboard to 0
    {   for(int j=0; j<COLS; j++)
            gameBoard2[i][j]=0;
    }
    
    
    startingPoint(ptrGame1, COLS);//create a starting point for the first gameboard
    
    
    for(int i=0; i<500; i++)//rund the game 500 times to see 500 generations
    {
       system("clear");//before each generation, clear the screen
       if (gens%2==0)//print rotating gameboards by sending either gameboard1 or gameboard2 to the print function
            print(ptrGame1, ROWS, COLS);
       else
            print(ptrGame2, ROWS,COLS);
        
        
	usleep(90000);//causes each generation to most momentarily so user can see the board before the change
        deadAlive(ptrGame1, ptrGame2, ROWS, COLS, gens);//run the function that makes updates to the board
       
        gens++;//increment the generations
        
        
  
    }
   
    
    
       return 0;
}

