//
//  Game.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iostream>
#include "Street.hpp"
#include "Space.hpp"
#include "Hero.hpp"
#include "Bar.hpp"
#include "Diner.hpp"
#include "Library.hpp"
#include "Airport.hpp"
#include "MonarchTowers.hpp"
#include "Door1.hpp"
#include "Door2.hpp"
#include "Door3.hpp"
#include "MainFrame.hpp"
#include "Winner.hpp"

class Game
{
private:
    Space* bar;
    Space* street;
    Space* diner;
    Space* library;
    Space* airport;
    Space* monarch;
    Space* door1;
    Space* door2;
    Space* door3;
    Space* mainframe;
    Space* winner;
    
    Hero bek;
    
public:
    void runGame();
    Game();
    ~Game();

    
    
    
};

#endif /* Game_hpp */
