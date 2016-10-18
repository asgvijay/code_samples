/**********************************************
 **** Program Filename: deadAlive.cpp
 **** Author: Vijay Kumar
 **** Date: 1/11/16
 **** Description: Conway's Game of Life
 ***************************************************/

#include "deadAlive.hpp"

/*************************************************************
 * This function tests if a cell in a gameboard is live or dead.
 * If a live cell as 2 or 3 live neighbors, the cell stays alive. 
 * We pass the result to the other gameboard. If the dead cell has
 * 3 live neighbors it becomes alive. This result is also passed to 
 * the new gameboard.
 * ****************************************************************/
void deadAlive(int *gameBoard1, int *gameBoard2, int row, int col, int gen)
{

    int counter=0; //this variable measure the rate of each cells neighbors
    
    
    if(gen%2 == 0) // if the gen agrument is even, we test one gameboard and send results to another gameboard
    {   for(int i =1; i<row; i++)// loop the increments the row
        {
            for(int j=1; j<col; j++)// loop that increments the col
            {
                if(gameBoard1[i*col + j] ==0)//if a certain cell is a 0, then we check for three live neighbors
                {
                    if(gameBoard1[(i*col-col)+ (j-1)]==1)
                        counter++;
                    if(gameBoard1[(i*col-col)+ j]==1)
                        counter++;
                    if(gameBoard1[(i*col-col)+(j+1)]==1)
                        counter++;
                    if(gameBoard1[(i*col)+(j-1)]==1)
                        counter++;
                    if(gameBoard1[i*col+(j+1)]==1)
                        counter++;
                    if(gameBoard1[(i*col+col)+(j-1)]==1)
                        counter++;
                    if(gameBoard1[(i*col+col)+(j)]==1)
                        counter++;
                    if(gameBoard1[(i*col+col)+(j+1)]==1)
                        counter++;
            
                    if(counter == 3)//if the cell has three live neighbors then the cell in the new gameboard becomes a 1
                        gameBoard2[i*col+j]=1;
                    else
                        gameBoard2[i*col+j]=0;// if the cell does not have three neighbors, new cell stays a zero
                    counter = 0;
                }
            

                else//this else is if the cell is a 1. Same function as previous if, but tests to see if cell has 2 or 3 live neighbors
                {
                    if(gameBoard1[(i*col-col)+ (j-1)]==1)
                        counter++;
                    if(gameBoard1[(i*col-col)+ j]==1)
                        counter++;
                    if(gameBoard1[(i*col-col)+(j+1)]==1)
                        counter++;
                    if(gameBoard1[(i*col)+(j-1)]==1)
                        counter++;
                    if(gameBoard1[i*col+(j+1)]==1)
                        counter++;
                    if(gameBoard1[(i*col+col)+(j-1)]==1)
                        counter++;
                    if(gameBoard1[(i*col+col)+(j)]==1)
                        counter++;
                    if(gameBoard1[(i*col+col)+(j+1)]==1)
                        counter++;
                
                    if(counter ==2 || counter == 3)
                        gameBoard2[i*col +j]=1;
                    else
                        gameBoard2[i*col+j]=0;
                    counter = 0;
                }
            
            }
        }
    
    }
    
    
    else// this else runs if the generation is in the odd numbers. Same operations as previous loops, but tests a different gameboard.
    {   for(int i =1; i<row; i++)
        {
            for(int j=1; j<col; j++)
            {
                if(gameBoard2[i*col+j] ==0)
                {
                    if(gameBoard2[(i*col-col)+ (j-1)]==1)
                        counter++;
                    if(gameBoard2[(i*col-col)+ j]==1)
                        counter++;
                    if(gameBoard2[(i*col-col)+(j+1)]==1)
                        counter++;
                    if(gameBoard2[(i*col)+(j-1)]==1)
                        counter++;
                    if(gameBoard2[i*col+(j+1)]==1)
                        counter++;
                    if(gameBoard2[(i*col+col)+(j-1)]==1)
                        counter++;
                    if(gameBoard2[(i*col+col)+(j)]==1)
                        counter++;
                    if(gameBoard2[(i*col+col)+(j+1)]==1)
                        counter++;
                
                    if(counter == 3)
                        gameBoard1[i*col+j]=1;
                    else
                        gameBoard1[i*col+j]=0;
                    counter = 0;
            }
            
            
            else
            {
                if(gameBoard2[(i*col-col)+ (j-1)]==1)
                    counter++;
                if(gameBoard2[(i*col-col)+ j]==1)
                    counter++;
                if(gameBoard2[(i*col-col)+(j+1)]==1)
                    counter++;
                if(gameBoard2[(i*col)+(j-1)]==1)
                    counter++;
                if(gameBoard2[i*col+(j+1)]==1)
                    counter++;
                if(gameBoard2[(i*col+col)+(j-1)]==1)
                    counter++;
                if(gameBoard2[(i*col+col)+(j)]==1)
                    counter++;
                if(gameBoard2[(i*col+col)+(j+1)]==1)
                    counter++;
                
                if(counter ==2 || counter == 3)
                    gameBoard1[i*col+j]=1;
                else
                    gameBoard1[i*col+j]=0;
                counter = 0;
            }
            
        }
    }
        
    }
    
}
