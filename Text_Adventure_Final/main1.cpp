#include "Game.hpp"
#include <iostream>

using std:: cout;
using std:: endl;
using std:: cin;

int main()
{	

	cout << "***********************************************" << endl;
	cout << "****************THE FINAL DAYS*****************" << endl;
	cout << "***********************************************" << endl;
	cout << endl;
	cout << "The year is 2080. Resources vital for human life have become rare and are now the highest traded commodity on the planet. Years ago drinkable water became unattainable for anyone but the uber rich. All others were forced to adopt sanitizing practices that left their water far from pure.\n\nNow, the world's oxygen is being siphoned from the atmosphere by a global corporation know as the Monarch Towers. Any city where Monarch Towers installed their giant oxygen absorbing buildings, left the remaining areas almost uninhabitable. All humans that have stayed in the area are suffering from oxygen-deprivation disease, and are forced to leave or they will soon perish.\n\nBeck, a former Monarch Towers engineer, is our hero on the threshold of a journey. In the surrounding city landscape, Beck must round up a team to break into Monarch Towers Main Frame where they can reverse the flow of oxygen and save the town from impending doom. And he must do it all without running out of his own oxygen reserve.\n" << endl;
    	cout << "Get to Monarch Towers, break into the Main Frame and crack the code to reverse the flow of oxygen. Do it all without your 'Oxygen Level' being completely exhausted.\n" << endl;
    	cout << "Let's begin."<< endl;
    	cout << "***********************************************" << endl;
    	cout << "Hit enter to continue." << endl;
    	cin.get();
   
    	//cin.ignore(10000, '\n');
	//cin.clear();
    	Game game1;
    	game1.runGame();
 
return 0;
}
