//
//  Game.cpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#include "Game.hpp"
#include <iostream>
using std:: cout;
using std:: endl;
using std:: cin;


Game:: Game()
{
    
    bar = new Bar; // create a new Bar
    street = new Street; // create a new Street
    diner = new Diner; // create a new Diner
    library = new Library; // create a new Library
    airport = new Airport; // create a new airport
    monarch = new MonarchTowers; // create new monarch towers
    door1 = new Door1; // create new door1
    door2 = new Door2; // create new door1
    door3 = new Door3; // create new door1
    mainframe = new MainFrame; // create mainframe room
    winner = new Winner; // create final winners circle
    
    
    street->setSpace(bar, diner, library, airport, street); // set all the ptrs for space
    bar->setSpace(street, diner, library, airport, bar);// set all the ptrs for space
    diner->setSpace(street, bar, library, airport, diner);// set all the ptrs for space
    library->setSpace(street, bar, diner, airport, library); // set all ptrs for space
    airport->setSpace(street, bar, library, monarch, airport); // set all ptrs for space
    monarch->setSpace(door1, door2 , door3, airport, monarch); // set all ptrs for space
    door1->setSpace(monarch, door2, door3 , mainframe, door1); // set all ptrs for space
    door2->setSpace(monarch, door1, door3 , mainframe, door2); // set all ptrs for space
    door3->setSpace(monarch, door1, door2 , mainframe, door3); // set all ptrs for space
    mainframe->setSpace(monarch, NULL, NULL, winner, mainframe); // set all ptrs for space
    
    bek.setWhere(street); // set hero's starting location
    
}

void Game:: runGame()
{
    while(bek.getWhere()->getSpaceName()!= "Winner" && bek.getOxyLev() > 0) // player gets to winners circle or runs out of oxy, we don't run loop
    {
        cout << "OXYGEN LEVEL: "  << bek.getOxyLev() << endl; // print player's oxy level
        bek.getWhere()->roomOptions(); // print the room options
        cout << endl;
        int choice;
        int error;
        do
        {
            error =0;
            cout << "Enter your choice." << endl;
            cin >> choice;
            if(cin.fail())
            {
                cout << "Please enter a valid integer." << endl;
                error=1;
                cin.clear();
                cin.ignore(80, '\n');
            }
	    if(choice<1 || choice>10)
		{	error=1;
			cout << "Please enter a valid menu option." << endl;
			
		}
        }while(error==1);
        
        if(bek.getWhere()->getVectorOption(choice) == 1) // if bad choice is made
        {
            int a = bek.getWhere()->badDecision();
            bek.setOxyLev(a);
            bek.getWhere()->removeOptions(choice); // remove the choice from the menu in the space
            cout << endl;
            cout << "Hit enter to continue." << endl;
            cin.get();
            cin.ignore();
        }
        else if(bek.getWhere()->getVectorOption(choice) == 2) // if friend choice is made
        {
            bek.addFriend(bek.getWhere()->beFriend());
            bek.getWhere()->removeOptions(choice); // remove the choice from the menu in the space
            cout << endl;
            cout << "Hit enter to continue." << endl;
            cin.get();
            cin.ignore();
            
        }
        else if(bek.getWhere()->getVectorOption(choice) == 3) // if key choice is made
        {
            bek.addKeys(bek.getWhere()->getKey());
            bek.getWhere()->removeOptions(choice); // remove the choice from the menu in the space
            bek.flushKeys();
            cout << endl;
            cout << "Hit enter to continue." << endl;
            cin.get();
            cin.ignore();
           
        }
        
        else if (bek.getWhere()->getVectorOption(choice) >=4 && bek.getWhere()->getVectorOption(choice) <=7)
        {    bek.setWhere(bek.getWhere()->moveOn(bek.getWhere()->getVectorOption(choice))); // if user decides to go somewhere else
            
        }
        else if (bek.getWhere()->getVectorOption(choice) ==10)
        {
            
            Space* temp = bek.getWhere();
            Space* change = bek.getWhere()->useAFriend(bek.getFriends());
            if(temp == change)
                bek.setOxyLev(40);
            bek.setWhere(change);
            cout << endl;
            cout << "Hit enter to continue." << endl;
            cin.get();
            cin.ignore();
        }
        else if (bek.getWhere()->getVectorOption(choice)==11)
        {
            Space* temp = bek.getWhere();
            Space* change = bek.getWhere()->useAFriend(bek.getNotes());
            if(temp == change)
                bek.setOxyLev(40);
            bek.setWhere(change);
            
        }
        
        
        else if(bek.getWhere()->getVectorOption(choice) == 8) // print friends
        {   bek.printFriends();
            cout << endl;
            cout << "Hit enter to continue." << endl;
            cin.get();
            cin.ignore();
        }
        
        else if(bek.getWhere()->getVectorOption(choice) == 9)
        {   bek.printKeys();
            cout << endl;
            cout << "Hit enter to continue." << endl;
            cin.get();
            cin.ignore();
        }
        else if(bek.getWhere()->getVectorOption(choice) == 12)
        {
            return;
        }
    
        for(int i=0; i<100; i++)
            cout << '\n';
        
    }
    
    if(bek.getWhere()->getSpaceName()=="Winner")
    {   cout << "You did it!!! You reversed the flow of oxygen and the town below immediately feels the difference. Your team rejoices with the victory for a moment before all the laughter calms. The feeling is undeniable, this team of the cemented have more to do, more towns to save. Now that the town is saved, it's time to save the world." << endl;
    
    }
    else
    {    cout << "You try to catch your breath but you can't. You pull in harder and harder, but nothing seems to work. Your body responds quickly to the lack of oxygen. You drop to your knees. You see stars. This is what it feels like. Numb. Dark. Time to sleep. Time to....\n\n" << endl;
        cout << "GAME OVER" << endl;
        
    }
    
    
    
}


Game:: ~Game()
{
    
    delete bar;
    delete street;
    delete diner;
    delete airport;
    delete monarch;
    delete door1;
    delete door2;
    delete door3;
    delete mainframe;
    delete winner;
    delete library;
    
}




