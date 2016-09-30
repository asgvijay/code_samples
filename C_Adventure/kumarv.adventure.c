// program 2
// Author: Vijay Kumar
// Date: 7/18/16

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <string.h>

struct room
    {
        
        char* room_connections[6];
        int room_count;
        char* room_name;
        int room;
        char* room_file;
        int start_room;
        int end_room;
    };


void addConnections(int taken_rooms[], char* room_names[], struct room* input_room, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7);

struct room* userChoice(char* selection, struct room* room1, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7);

struct room* findStartRoom(struct room* room1, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7);
  
int roomExist(char* selection, struct room* currRoom);

void addPath(int* num, char* room_names[], char* room);

void initializeRooms(struct room* room1, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7);

int main()
{
    
    //////////////////////////////////////////////////////////////
    /////////////////// GAME SETUP ///////////////////////////////
    //////////////////////////////////////////////////////////////
    
    // randomizer
    srand(time(NULL));
    
    // create 7 rooms
    struct room room1;
    struct room room2;
    struct room room3;
    struct room room4;
    struct room room5;
    struct room room6;
    struct room room7;
    
    // create pointers to room for use with functions
    struct room* room1ptr = &room1;
    struct room* room2ptr = &room2;
    struct room* room3ptr = &room3;
    struct room* room4ptr = &room4;
    struct room* room5ptr = &room5;
    struct room* room6ptr = &room6;
    struct room* room7ptr = &room7;
    
    // intialize rooms
    initializeRooms(room1ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr);
    
    // create 7 different room files in directory kumar.v.rooms.<processid>
    
    int pid = getpid(); // get current id
    char dirName[NAME_MAX+1]; // create string to hold directory name
    char* prefix = "kumarv.rooms."; // create a prefix for the directory name
    snprintf(dirName, NAME_MAX + 1, "%s%d", prefix, pid); // push prefix and pid to dirname variable
    
    struct stat st = {0};// create struct to store info about file
    
    if(stat(dirName, &st) == -1) // if the directory doesn't exist.
    {
        mkdir(dirName, 0755);
           
    }
    
    char* room_names[10]; // create an array of possible room names
    
    room_names[0] = "The Sun";
    room_names[1] = "Planet Mercury";
    room_names[2] = "Planet Venus";
    room_names[3] = "Planet Earth";
    room_names[4] = "Planet Mars";
    room_names[5] = "Planet Jupiter";
    room_names[6] = "Planet Saturn";
    room_names[7] = "Planet Uranus";
    room_names[8] = "Planet Neptune";
    room_names[9] = "Planet Nine";
        
    int taken_rooms[10];    // keep track of which rooms are being used
    char* gamePath[20];     // keep track of rooms visited
    int numberOfRooms =0;   // keep track of number of rooms visited
    int random_room;        // for random selection of room
    int num_connections;    // count number of connections for room
    int i;                  // for loop index
    
    char fileName[NAME_MAX+1]; // variable for opening files
    
    
    ///////////// SETUP ROOM NAMES, IDs, and FILENAME PREFIX /////////////////////
    
    ///////////// Room 1 /////////////////////////////
    snprintf(fileName, NAME_MAX + 1, "%s/room1.txt", dirName); 
    FILE *room =fopen(fileName, "w"); // open room1 file
    
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]); // send room name to file
    room1.room = random_room; // remember room assignment
    room1.room_name = room_names[random_room];
    room1.room_file = "/room1.txt";
    
    fclose(room); // close file
    
    ///////// Room 2 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room2.txt", dirName);
    room = fopen(fileName, "w"); // open room2 file
    
   //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]);// send room name to file
    
    room2.room = random_room; // remember room assignment
    room2.room_name = room_names[random_room];
    room2.room_file = "/room2.txt";
    fclose(room); // close file
    
    /////////// Room 3 ///////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room3.txt", dirName);
    room = fopen(fileName, "w");// open room3 file
    
      //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]);// send room name to file
    
    room3.room = random_room; // remember room assignment
    room3.room_name = room_names[random_room];
    room3.room_file = "/room3.txt";
    
    fclose(room);// close file
    
    /////////////////Room 4//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room4.txt", dirName);
    room = fopen(fileName, "w");// open room4 file
    
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]);// send room name to file
    
    room4.room = random_room; // remember room assignment
    room4.room_name = room_names[random_room];
    room4.room_file = "/room4.txt";
    
    fclose(room);// close file
    
    /////////////////Room 5//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room5.txt", dirName);
    room = fopen(fileName, "w");// open room5 file
    
     //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]);
    
    room5.room = random_room; // remember room assignment
    room5.room_name = room_names[random_room];
    room5.room_file = "/room5.txt";
    
    fclose(room);// close file
    
    /////////////////Room 6//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room6.txt", dirName);
    room = fopen(fileName, "w");
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]);// send room name to file
    
    room6.room = random_room; // remember room assignment
    room6.room_name = room_names[random_room];
    room6.room_file = "/room6.txt";
    
    fclose(room);// close file
    
    /////////////////Room 7//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room7.txt", dirName);
    room = fopen(fileName, "w");// open room6 file
    
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "CURRENT LOCATION: ", room_names[random_room]);// send room name to file
    
    room7.room = random_room; // remember room assignment
    room7.room_name = room_names[random_room];
    room7.room_file = "/room7.txt";
    
    fclose(room);// close file
    
    
    
    
    ///////////// SETUP ROOM CONNCECTIONS /////////////////////
    
    addConnections(taken_rooms, room_names, room1ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr);
    addConnections(taken_rooms, room_names, room2ptr, room1ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr);
    addConnections(taken_rooms, room_names, room3ptr, room2ptr, room1ptr, room4ptr, room5ptr, room6ptr, room7ptr);
    addConnections(taken_rooms, room_names, room4ptr, room2ptr, room3ptr, room1ptr, room5ptr, room6ptr, room7ptr);
    addConnections(taken_rooms, room_names, room5ptr, room2ptr, room3ptr, room4ptr, room1ptr, room6ptr, room7ptr);
    addConnections(taken_rooms, room_names, room6ptr, room2ptr, room3ptr, room4ptr, room5ptr, room1ptr, room7ptr);
    addConnections(taken_rooms, room_names, room7ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room1ptr);
    
    ///////////// SAVE ROOM DATA TO FILE /////////////////////
    
    /////////////////Room 1//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room1.txt", dirName);
    room = fopen(fileName, "a");// open room1 file
    
   for(i = 0 ; i< room1.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room1ptr->room_connections[i]);// add connections to file
          
    }
    
   fclose(room);// close file
    
    /////////////////Room 2//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room2.txt", dirName);
    room = fopen(fileName, "a");// open room2 file
    
   for(i = 0 ; i< room2.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room2.room_connections[i]);// add connections to file
        
        
    }
   
    fclose(room);// close file
    
    /////////////////Room 3//////////////////////////////////
    snprintf(fileName, NAME_MAX + 1, "%s/room3.txt", dirName);
    room = fopen(fileName, "a");// open room3 file
    
   for(i = 0 ; i< room3.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room3ptr->room_connections[i]);// add connections to file
        
        
    }
   
    fclose(room);// close file
    
    /////////////////Room 4//////////////////////////////////
    
      snprintf(fileName, NAME_MAX + 1, "%s/room4.txt", dirName);
    room = fopen(fileName, "a");// open room4 file

   for(i = 0 ; i< room4.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room4ptr->room_connections[i]);// add connections to file
        
        
    }
  
    fclose(room);// close file
    
    /////////////////Room 5//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room5.txt", dirName);
    room = fopen(fileName, "a");// open room5 file

   for(i = 0 ; i< room5.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room5ptr->room_connections[i]);// add connections to file
        
        
    }
 
    fclose(room);// close file
    
    /////////////////Room 6//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room6.txt", dirName);
    room = fopen(fileName, "a");// open room6 file
    
   for(i = 0 ; i< room6.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room6ptr->room_connections[i]);// add connections to file
        
        
    }
    
    fclose(room);// close file
    
    /////////////////Room 7//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room7.txt", dirName);
    room = fopen(fileName, "a");// open room7 file
    

   for(i = 0 ; i< room7.room_count; i++)
    {
        fprintf(room, "%s%s\n", "CONNECTION: ", room7ptr->room_connections[i]);// add connections to file
        
        
    }
  
   
    fclose(room);// close file
    
     ///////////// SET ROOM TYPES /////////////////////
    
    int start_room = rand() % 10;       // random number generator
    while(taken_rooms[start_room] != 1) // if room is taken try again
        start_room = rand() % 10;
    
    int end_room = rand() % 10;         // random number generator
    while(start_room == end_room || taken_rooms[end_room]!=1) // if room is taken or == to start room, try again
        end_room = rand() %10;
    
   
    /////////////////// Room 1 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room1.txt", dirName);
    room = fopen(fileName, "a");        // open file
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room1.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room1.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room1.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room1.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
      /////////////////// Room 2 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room2.txt", dirName);
    room = fopen(fileName, "a");
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room2.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room2.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room2.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room2.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
      /////////////////// Room 3 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room3.txt", dirName);
    room = fopen(fileName, "a");
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room3.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room3.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room3.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room3.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
    
    
      /////////////////// Room 4 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room4.txt", dirName);
    room = fopen(fileName, "a");
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room4.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room4.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room4.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room4.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
    
    
      /////////////////// Room 5 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room5.txt", dirName);
    room = fopen(fileName, "a");
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room5.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room5.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room5.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room5.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
    
      /////////////////// Room 6 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room6.txt", dirName);
    room = fopen(fileName, "a");
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room6.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room6.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room6.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room6.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
      /////////////////// Room 7 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room7.txt", dirName);
    room = fopen(fileName, "a");
    
    // find if room is start, mid, or end. Send room type info to file
    if(room_names[start_room] == room_names[room7.room])
    {
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
        room7.start_room = 1;
    }
    else if(room_names[end_room] == room_names[room7.room])
    {  
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
        room7.end_room = 1;
    }
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);// close file
    
    /////////////////// END GAME SETUP ///////////////////////////
    
    //////////////////////////////////////////////////////////////
    /////////////////// COMMENCE GAME ////////////////////////////
    //////////////////////////////////////////////////////////////
    
    printf("///////////////// PHONE HOME /////////////////////////\n\n");
    printf("You've woken up somewhere mysterious. This isn't your home.\n");
    printf("Not only is this not your bed, this isn't your home, nor is it even your planet.\n");
    printf("No time to worry about how you got here.\nJust focus on getting home, as this isn't the most welcoming environment.\n\n");
    
    char line[NAME_MAX + 1]; // string for printing to screen
    
    ///////////////////// OPEN START ROOM ///////////////////
    
    // find start room
    struct room* start = findStartRoom(room1ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr);
    
    //add room to path
    addPath(&numberOfRooms, gamePath, start->room_name);
    
    
    //open file
    snprintf(fileName, NAME_MAX + 1, "%s%s", dirName, start->room_file);
    room = fopen(fileName, "r");
    
    char *arg;      // interator for string parsing
    
    
    // print contents to screen
    fgets(line,NAME_MAX+1, room);   // grab first line
    arg = strchr(line, ':');        // point iterator to the ":" in line
    arg++;                          // increment pointer to skip spaces
    arg++;
    line[strcspn(line, "\n")] = 0;  // strip null terminator from line
    printf("CURRENT LOCATION: ");   // print header for line
    printf("%s\n", arg);            // print the line received by fgets
    
    printf("POSSIBLE CONNECTIONS: ");   // print header for connections
    int rooms_printed = 0;              // counter for rooms printed
    
    while(fgets(line, NAME_MAX+1, room))    // print the remaining lines found in file
    {
        arg = strchr(line, ':');            // point iterator at ":" in line
        arg++;                              // increment to skip spaces
        arg++;
        line[strcspn(line, "\n")] = 0;      // strip null terminator in line
        
        if(strstr(line, "CONNECTION") && rooms_printed<start->room_count-1) // if line begins with "CONNECTION" print the line. Only print to the second to last line in connections
        {  
            printf("%s, ", arg);            // print room name
            rooms_printed++;                // count the number of rooms that have been printed
        }
         
         else if(strstr(line, "CONNECTION"))    // print last line in connections and add "."
            printf("%s.\n", arg);

    }
    
    printf("\n");
    
    printf("Where To? > ");                     // print line and allow user to input after >
    
    char userInput[NAME_MAX + 1];               // string for user input
   
    fgets(userInput, NAME_MAX + 1, stdin);      // get user input
   
    while(roomExist(userInput, start)==0)       // if does NOT exist run while loop with prompt for user to try again
    {
        printf("Uh-Oh, That planet doesn't exist, it is your current planet, or your input was just a bit off.\nPlease try again.\n");
        fgets(userInput, NAME_MAX + 1, stdin);
        
    }
    
    fclose(room);                               // close starting room file.
    
    ////////////////////// FIND NEXT ROOM ////////////////////////
  
    // find next room
    struct room* roomChoice = userChoice(userInput, room1ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr); 
   
    while(roomChoice->end_room != 1)            // while loop iterates game through rooms until END_ROOM is found
    {
        snprintf(fileName, NAME_MAX + 1, "%s%s", dirName, roomChoice->room_file);
        room = fopen(fileName, "r");            // open file
    
    // NEW print contents
    
    fgets(line,NAME_MAX+1, room);               // get first line from room file
    arg = strchr(line, ':');                    // point iterator to the ":" in line
    arg++;  
    arg++;                                      // increment to skip spaces
    line[strcspn(line, "\n")] = 0;              // strip null terminator in line
    printf("CURRENT LOCATION: ");               // print header
    printf("%s\n", arg);                        // print room name
    
    printf("POSSIBLE CONNECTIONS: ");           // print connections header
    int rooms_printed = 0;                      // count rooms printed      
        
    while(fgets(line, NAME_MAX+1, room))        // loop as long as there are lines to be read.
    {
        arg = strchr(line, ':');                // point iterator to the ":" in line
        arg++;                                  // increment to skip spaces
        arg++;
        line[strcspn(line, "\n")] = 0;          // strip null terminator in line
        
        if(strstr(line, "CONNECTION") && rooms_printed<start->room_count-1)// if line begins with "CONNECTION" print the line. Only print to the second to last line in connections
        {  
            printf("%s, ", arg);                 // print room name
            rooms_printed++;                     // increment room counter
        }
         
         else if(strstr(line, "CONNECTION"))     // print last line in connections and add "."
            printf("%s.\n", arg);

    }
    
    printf("\n");
        
        
        
        printf("Where To? > ");                     // print line and allow user to input after >
      
        fgets(userInput, NAME_MAX + 1, stdin);      // get user input
    
        while(!roomExist(userInput, roomChoice))    // if user input doesn't exist repeat loop and ask for input
        {
            printf("Uh-Oh, That planet doesn't exist, it is your current planet, or your input was just a bit off.\nPlease try again.\n");
            fgets(userInput, NAME_MAX + 1, stdin);

        }
        
        addPath(&numberOfRooms, gamePath, roomChoice->room_name);  // add room to path for final printing
        
        // find new room choice
        roomChoice = userChoice(userInput, room1ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr);

        fclose(room); // close current room file
    
    }
    
    //////////////////////// FINALIZE GAME //////////////////////////////////
    
    addPath(&numberOfRooms, gamePath, roomChoice->room_name); // add end room to path
    
    // print the winners cry
    printf("Wow! You have found the End Room!\n");          
    
    // print the number of steps taken
    printf("It took you %d steps to make it to the final room.\n", numberOfRooms -1);
    
    // print the order of rooms visited
    printf("The rooms you visited in order are: \n");
    for(i=0; i< numberOfRooms; i++)
    {
        printf("%s\n", gamePath[i]);
    }
    
    //////////////////////////////////////////////////////////////
    /////////////////// END GAME /////////////////////////////////
    //////////////////////////////////////////////////////////////
   
return 0;
}

////////////////////////////////////////////////////////////////////
////////////////////////ADDPATH FUNCTION////////////////////////////
// addPath adds a pointer to a room at the end of the array. The num
// variable is incremented for appropriate assignment during next 
// addPath() call. 
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void addPath(int* num, char* room_names[], char* room)
{
    room_names[*num] = room;  // add new room to the path of visited rooms
    (*num)++;                 // increment the array count
    
    
}

////////////////////////////////////////////////////////////////////
////////////////////////ROOMEXIST FUNCTION//////////////////////////
// roomExist finds if a user input exists as a room in the game.
// If the selection exists, return 1, else return 0
// selection var is the user input. room* is players current room
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int roomExist(char* selection, struct room* currRoom)
{
    selection[strcspn(selection, "\n")] = 0; // strip the null terminator from line
    int i =0;
  
    for(i =0; i<currRoom->room_count; i++)    // iterate through each room in the current room's connection list
    {
        if(strcmp(selection,currRoom->room_connections[i])==0) // compare the user input to room i
           return 1;                                            // if room exists return 1
        
      
    }
    
    return 0;                                   // if room doesn't exist return 0
}

////////////////////////////////////////////////////////////////////
////////////////////////FINDSTARTOOM FUNCTION///////////////////////
// findStartRoom checks all rooms in the game to and returns the 
// room labeled as the start room.
// The parameters are all seven rooms.
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

struct room* findStartRoom(struct room* room1, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7)
{
     if(room1->start_room == 1)                 // if room's start_room variable is set to 1, return the room.
        return room1;
    
     else if(room2->start_room == 1)
        return room2;
    
     else if(room3->start_room == 1)
        return room3;
    
     else if(room4->start_room == 1)
        return room4;
    
    else if(room5->start_room == 1)
        return room5;
    
     else if(room6->start_room == 1)
        return room6;
    
     else if(room7->start_room == 1)
        return room7;
    
    else
        return NULL;                                // if none of the room's variables are 1, return 0.
    
    
    
    
}

////////////////////////////////////////////////////////////////////
////////////////////////USERCHOICE FUNCTION/////////////////////////
// userChoice takes the user input and tries to match to all the 
// room names. If found, the room is returned, else return NULL
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

struct room* userChoice(char* selection, struct room* room1, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7)
{
    selection[strcspn(selection, "\n")] = 0;        // strip the null terminator from line
    
    if(strcmp(selection, room1->room_name)==0)      // compare room names to user input, return room if a compare is found
        return room1;
    
     else if(strcmp(selection, room2->room_name)==0)
        return room2;
    
     else if(strcmp(selection, room3->room_name)==0)
        return room3;
    
     else if(strcmp(selection, room4->room_name)==0)
        return room4;
    
    else if(strcmp(selection, room5->room_name)==0)
        return room5;
    
     else if(strcmp(selection, room6->room_name)==0)
        return room6;
    
     else if(strcmp(selection, room7->room_name)==0)
        return room7;
    
    else
        return NULL;                                // if no matches are found, return 1
    
}




////////////////////////////////////////////////////////////////////
////////////////////////ADDCONNECTIONS FUNCTION/////////////////////
// addConnections randomly assigns connections to each room. 
// If a connection is made from room A to room B, room B will have
// a connection to room B. All rooms can contain up to 6 connections 
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void addConnections(int taken_rooms[], char* room_names[], struct room* input_room, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7)
{

    int num_connections = rand() % (6 - 3 +1) + 3;      // create random number between 3 and 6
    
    int random;
    
    while(num_connections>0 && input_room->room_count<6)    // while loop runs until the input_room has hit connection limit
    {
        int check = 0; // boolean check
        
        do
        {
            random = rand() % 10;       // random number for room assignment
            check = 0;
            
            // make sure new random room is available and that it is not trying to add itself
            while(taken_rooms[random] != 1 || room_names[random] == input_room->room_name)
                random = rand() % 10;
              
            int i=0;
            
            // check to make sure room doesn't already exist on list
            if(input_room->room_count !=0)
            {
                for(i =0; i< input_room->room_count; i++)
                {    
                    if(room_names[random] == input_room->room_connections[i])
                    { 
                        check = 1;    // if room name already exists on list, we flag the check var and continue do/while   
                    }
                }
            }
        }while(check==1);
      
        
        char* room_choice = room_names[random]; // room we're trying to add

        //find which room has this name and make adjustments

   
        if(room2->room_name == room_choice && room2->room_count < 6) // if room2 is the connection attempt
        {

            room2->room_connections[room2->room_count] = input_room->room_name; // add input room to room2 connections
            room2->room_count++;                        // increment room2 count
            input_room->room_connections[input_room->room_count]= room_choice; // add room2 to input_room connections
            input_room->room_count++;   // increment input_room count
            num_connections--;          // decrement number of connections needed.

        }

        // same process as described in room2
        else if(room3->room_name == room_choice && room3->room_count < 6)
        {
            room3->room_connections[room3->room_count] = input_room->room_name;
            room3->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;
             num_connections--;

        }

        else if(room4->room_name == room_choice && room4->room_count < 6)
        {
            room4->room_connections[room4->room_count] = input_room->room_name;
            room4->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;
            num_connections--;

        }

        else if(room5->room_name == room_choice && room5->room_count < 6)
        {
            room5->room_connections[room5->room_count] = input_room->room_name;
            room5->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;
            num_connections--;

        }

        else if(room6->room_name == room_choice && room6->room_count < 6)
        {
            room6->room_connections[room6->room_count] = input_room->room_name;
            room6->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;
            num_connections--;

        }

        else if(room7->room_name == room_choice && room7->room_count < 6)
        {
            room7->room_connections[room7->room_count] = input_room->room_name;
            room7->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;
            num_connections--;
        }

            
            
            
    }
            
            
            
}


////////////////////////////////////////////////////////////////////
////////////////////////INITIALIZEROOMS FUNCTION////////////////////
// initializeRooms intializes crucial variables in the rooms to zero
// All rooms must be sent in as parameters
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void initializeRooms(struct room* room1, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7)
{
    
    room1->room_count = 0;
    room2->room_count = 0;
    room3->room_count = 0;
    room4->room_count = 0;
    room5->room_count = 0;
    room6->room_count = 0;
    room7->room_count = 0;
    
    room1->start_room = 0;
    room2->start_room = 0;
    room3->start_room = 0;
    room4->start_room = 0;
    room5->start_room = 0;
    room6->start_room = 0;
    room7->start_room = 0;
    
    room1->end_room = 0;
    room2->end_room = 0;
    room3->end_room = 0;
    room4->end_room = 0;
    room5->end_room = 0;
    room6->end_room = 0;
    room7->end_room = 0;
    
}
    
    
    
    
    
