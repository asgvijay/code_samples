// program 2

//#include "kumarad.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>

void testerfunction();

 struct room
    {
        
        char* room_connections[6];
        int room_count;
        char* room_name;
        int room;
    };






int main()
{
    
    testmain();
    // randomizer
    srand(time(NULL));
    
    struct room room1;
    struct room room2;
    struct room room3;
    struct room room4;
    struct room room5;
    struct room room6;
    struct room room7;
    
    struct room* room1ptr = &room1;
    struct room* room2ptr = &room2;
    struct room* room3ptr = &room3;
    struct room* room4ptr = &room4;
    struct room* room5ptr = &room5;
    struct room* room6ptr = &room6;
    struct room* room7ptr = &room7;
    
    
    // create 7 different room files in directory kumar.v.rooms.<processid>
    
    int pid = getpid();
    char dirName[NAME_MAX+1];
    char* prefix = "kumarv.rooms.";
    snprintf(dirName, NAME_MAX + 1, "%s%d", prefix, pid);
    
    struct stat st = {0};
    
    if(stat(dirName, &st) == -1)
    {
        mkdir(dirName, 0755);
           
    }
    
    char* room_names[10];
    
    room_names[0] = "Sun Room";
    room_names[1] = "Mercury Room";
    room_names[2] = "Venus Room";
    room_names[3] = "Earth Room";
    room_names[4] = "Mars Room";
    room_names[5] = "Jupiter Room";
    room_names[6] = "Saturn Room";
    room_names[7] = "Uranus Room";
    room_names[8] = "Neptune Room";
    room_names[9] = "Poor Pluto Room";
        
    int taken_rooms[10];
    int connected_rooms[10][10];
    
   /*
    char* room2_connections[6];
    int room2_count = 0;
    char* room3_connections[6];
    int room3_count = 0;
    char* room4_connections[6];
    int room4_count = 0;
    char* room5_connections[6];
    int room5_count = 0;
    char* room6_connections[6];
    int room6_count = 0;
    char* room7_connections[6];
    int room7_count = 0;
    
    char* room1_name;
    char* room2_name;
    char* room3_name;
    char* room4_name;
    char* room5_name;
    char* room6_name;
    char* room7_name;
    
    int room1, room2, room3, room4, room5, room6, room7;
    */
    
    int random_room;
    int num_connections;
    int i;
    
    char fileName[NAME_MAX+1];
    
    ///////////// Room 1 /////////////////////////////
    snprintf(fileName, NAME_MAX + 1, "%s/room1.txt", dirName);
    FILE *room =fopen(fileName, "w");
    
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    room1.room = random_room; // remember room assignment
    room1.room_name = room_names[random_room];
    
    fclose(room);
    
    ///////// Room 2 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room2.txt", dirName);
    room = fopen(fileName, "w");
    
   //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    
    room2.room = random_room; // remember room assignment
    room2.room_name = room_names[random_room];
    fclose(room);
    
    /////////// Room 3 ///////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room3.txt", dirName);
    room = fopen(fileName, "w");
      //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    
    room3.room = random_room; // remember room assignment
    room3.room_name = room_names[random_room];
    fclose(room);
    
    /////////////////Room 4//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room4.txt", dirName);
    room = fopen(fileName, "w");
    
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    
    room4.room = random_room; // remember room assignment
    room4.room_name = room_names[random_room];
    fclose(room);
    
    /////////////////Room 5//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room5.txt", dirName);
    room = fopen(fileName, "w");
     //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    
    room5.room = random_room; // remember room assignment
    room5.room_name = room_names[random_room];
    fclose(room);
    
    /////////////////Room 6//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room6.txt", dirName);
    room = fopen(fileName, "w");
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    
    room6.room = random_room; // remember room assignment
    room6.room_name = room_names[random_room];
    fprintf(room, "%s", "ROOM TYPE: MID_ROOM\n");
    fclose(room);
    
    /////////////////Room 7//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room7.txt", dirName);
    room = fopen(fileName, "w");
    //randomly sets room name
    random_room = rand() % 10;
    while(taken_rooms[random_room] == 1) // if room is set to 1, then room already reserved. try again.
        random_room = rand() %10;
    taken_rooms[random_room] = 1; // reserve the room
    
    fprintf(room, "%s%s\n", "ROOM NAME: ", room_names[random_room]);
    
    room7.room = random_room; // remember room assignment
    room7.room_name = room_names[random_room];
    fclose(room);
    
    
    
    
    //////////////////// Room Connections /////////////////////////
    
    /////////////////Room 1//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room1.txt", dirName);
    room = fopen(fileName, "a");
    
    // set number of connections
    num_connections = rand() % 6 + 1;
   // addConnections(taken_rooms, room_names, room1ptr, room2ptr, room3ptr, room4ptr, room5ptr, room6ptr, room7ptr);
    
    
    //check for pre-connected rooms
    
   
    
   fclose(room);
    
    /////////////////Room 2//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room2.txt", dirName);
    room = fopen(fileName, "a");
    
    
    
    fclose(room);
    
    /////////////////Room 3//////////////////////////////////
    snprintf(fileName, NAME_MAX + 1, "%s/room3.txt", dirName);
    room = fopen(fileName, "a");
    
    
     // set number of connections
    num_connections = rand() % 6 + 1;
    
   
    fclose(room);
    
    /////////////////Room 4//////////////////////////////////
    
      snprintf(fileName, NAME_MAX + 1, "%s/room4.txt", dirName);
    room = fopen(fileName, "a");
    
    
     // set number of connections
    num_connections = rand() % 6 + 1;
    
   
    fclose(room);
    
    /////////////////Room 5//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room5.txt", dirName);
    room = fopen(fileName, "a");
    
    
     // set number of connections
    num_connections = rand() % 6 + 1;
    
   
    fclose(room);
    
    /////////////////Room 6//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room6.txt", dirName);
    room = fopen(fileName, "a");
    
    
     // set number of connections
    num_connections = rand() % 6 + 1;
    
   
    fclose(room);
    
    /////////////////Room 7//////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room7.txt", dirName);
    room = fopen(fileName, "a");
    
    
     // set number of connections
    num_connections = rand() % 6 + 1;
    
    
    fclose(room);

    ///////////////// Room Type /////////////////////////////////
    
    int start_room = rand() % 10;
    while(taken_rooms[start_room] != 1)
        start_room = rand() % 10;
    int end_room = rand() % 10;
    while(start_room == end_room || taken_rooms[end_room]!=1)
        end_room = rand() %10;
    
   
    /////////////////// Room 1 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room1.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room1.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room1.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
      /////////////////// Room 2 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room2.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room2.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room2.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
      /////////////////// Room 3 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room3.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room3.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room3.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
    
    
      /////////////////// Room 4 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room4.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room4.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room4.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
    
    
      /////////////////// Room 5 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room5.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room5.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room5.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
    
      /////////////////// Room 1 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room6.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room6.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room6.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
      /////////////////// Room 1 ////////////////////////////////
    
    snprintf(fileName, NAME_MAX + 1, "%s/room7.txt", dirName);
    room = fopen(fileName, "a");
    
    if(room_names[start_room] == room_names[room7.room])
        fprintf(room, "%s\n", "ROOM TYPE: START_ROOM");
    else if(room_names[end_room] == room_names[room7.room])
        fprintf(room, "%s\n", "ROOM TYPE: END_ROOM");
    else 
        fprintf(room, "%s\n", "ROOM TYPE: MID_ROOM");
        
    fclose(room);
    
    
    
    
    
return 0;
}
/*

void addConnections(int taken_rooms[], char* room_names[], struct room* input_room, struct room* room2, struct room* room3, struct room* room4, struct room* room5, struct room* room6, struct room* room7)
{

    int num_connections = rand() % (6 - 3 +1) + 3;
    
    while(num_connections>0)
    {
        int random = rand() % 10;

        while(taken_rooms[random] != 1 || room_names[random] == input_room->room_name)
            random = random = rand() % 10;

        char* room_choice = room_names[random]; // room we're trying to add

        //find which room has this name and make adjustments

   
        if(room2->room_name == room_choice && room2->room_count < 6)
        {

            room2->room_connections[room2->room_count] == input_room->room_name;
            room2->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;


        }

        else if(room3->room_name == room_choice && room3->room_count < 6)
        {
            room3->room_connections[room3->room_count] == input_room->room_name;
            room3->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;


        }

        else if(room4->room_name == room_choice && room4->room_count < 6)
        {
            room4->room_connections[room4->room_count] == input_room->room_name;
            room4->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;


        }

        else if(room5->room_name == room_choice && room5->room_count < 6)
        {
            room5->room_connections[room5->room_count] == input_room->room_name;
            room5->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;


        }

        else if(room6->room_name == room_choice && room6->room_count < 6)
        {
            room6->room_connections[room6->room_count] == input_room->room_name;
            room6->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;


        }

        else if(room7->room_name == room_choice && room7->room_count < 6)
        {
            room7->room_connections[room7->room_count] == input_room->room_name;
            room7->room_count++;
            input_room->room_connections[input_room->room_count]= room_choice;
            input_room->room_count++;

        }

            
            
            
    }
            
            
            
}
*/

void testerfunction()
{
    printf("test");
}



   
    
    
    
    
    
