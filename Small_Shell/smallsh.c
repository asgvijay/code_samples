#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define MAX_LENGTH 2048
#define MAX_ARGS 512   
#define DEBUG 0

char* getArgs();                                    // function to get user input
char** parseLine(char* line, int* bgFlag);          // function to parse user input
void processBgArray(pid_t *bgArray, int *count);    // function to record bg processes
void findCarrots(char** command, int* inputIndex, int* outputIndex);    // function to find redirection commands
void cdCommand(char** command);                                         // function to change directory
void exitCommand(int *count, pid_t *bgArray); // function to exit shell
int commandType(char** command);                                        // function to decipher type of command entered
pid_t cpid;                                         // global var for child process pid
pid_t fgpid;                                        // global var for foreground process pid
int fd;                                             // global var for redirections
int fd2;                                            // global var for redirections

int main()
{
    // set up sigaction structures
    struct sigaction defaultSA;                     // sig structure to be used with child
    struct sigaction ignoreSA;                      // sig struecture to be used with parent
    ignoreSA.sa_handler = SIG_IGN;                  // add signal handlers
    defaultSA.sa_handler = SIG_DFL;
    int again = 1;                                  // loop variable -- Do we loop again?
    
    char* line;                                     // string to hold user input
    line = (char*)malloc(MAX_LENGTH *sizeof(char)); // initialize
    if(!line)                                       // ensure line initializes correctly
    {
        fprintf(stderr, "Line not initialized correctly.");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    char** args = malloc(MAX_ARGS *sizeof(char*));  // array of strings to hold parsed command
    if(!args)                                       // ensure args initializes correcty
    {
        fprintf(stderr, "Args not initialized correctly.");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    pid_t bgArray[1000];                        // array to hold background pids
    int bgArrayCount = 0;                       // count measuring how many pids in array
    int bgFlag = 0;                             // flag for testing if command is for bg process
    int status = 0;                             // holds status or last process
    int commandtype;                            // var for measuring what type of command input is
    int inputIndex = -1;                        // vars to hold the index of redirection carrots
    int outputIndex = -1;
    int exitStatus;                             // var to aid in error messaging
    char* statusMessage = malloc(100* sizeof(char));    // string to hold status message
    if(!statusMessage)                                       // ensure status message initializes correcty
    {
        fprintf(stderr, "statusMessage not initialized correctly.");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    int i;
    
    // This loop runs the core of our shell. Upon exit, the "again" flag is set to zero and the loop is not continued
    
    while(again==1)
    {
        
        fflush(stdout);                         // flush input/output streams
        fflush(stdin);
        processBgArray(bgArray, &bgArrayCount); //process any background pid
        printf(": ");                           //print colon
        fflush(stdout);                         //flush stdout
        line = getArgs();                       //get line from arguments
        fflush(stdin);                          //flush
        args = parseLine(line, &bgFlag);        //break up line into its constituent parts
        if(DEBUG)
        {
            i=0;
            
            while(args[i]!=NULL)
            {
                printf("My args are %s\n", args[i]);
                i++;
            }
        }
      
        commandtype = commandType(args);        // decipher what type of command input is (built-in or exec)
    
        ////////////////////////////IF COMMAND IS EXIT//////////////////////////////////////
        if(commandtype ==1)
        {  if(DEBUG)
                    printf("before exitCommand()\n");
                
            exitCommand(&bgArrayCount, bgArray); // exit current process
            again = 0;
            break;
        }
        
        ////////////////////////////IF COMMAND IS CD//////////////////////////////////////
        else if(commandtype == 2) 
        {
            if(DEBUG)
                    printf("before cdCommand()\n");
            cdCommand(args);                // change to appropriate directory
            
        }
        
        ////////////////////////////IF COMMAND IS STATUS//////////////////////////////////////
        else if(commandtype == 3)
        {
            printf("%s\n", statusMessage);  // print the most recent status message
            fflush(stdout);
               
        }
        
        ////////////////////////////IF COMMAND IS # COMMENT//////////////////////////////////////
        else if(commandtype == 4)
            continue;
        
        ////////////////////////////IF COMMAND IS NOT BUILT-IN//////////////////////////////////////
        else
        {
              if(DEBUG)
                    printf("before fork()\n");
                
                cpid = fork();                  // fork the current process
            
                ////////////WHEN WE ARE IN CHILD PROCESS////////////////////////
                
                if(cpid ==0) // in child process
                {
                    if(!bgFlag)
                        sigaction(SIGINT, &defaultSA, NULL); // set interrupt handler for fg process if child process is for background
                    
                    findCarrots(args, &inputIndex, &outputIndex); // find indices for redirection if they exist
                    
                    ////////////HANDLE INPUT////////////////////////

                    if(inputIndex >-1) // < was found and inputIndex holds its index
                    {  
                        
                            fd = open(args[inputIndex+1], O_RDONLY); // input
                            if (fd == -1) // if we can't open file for reading
                            {
                                printf("Cannot open %s\n", args[inputIndex+1]);
                                fflush(stdout);
                                exit(1); 
                            }
                            if(DEBUG)
                                printf(" In Child before dup2()\n");
                            fd2 = dup2(fd,0);                       // redirection of input
                            if (fd2 == -1)
                            {
                                printf("Cannot open %s\n", args[inputIndex+1]);
                                fflush(stdout);
                                exit(1);
                            }
                    }

               
                    else    // no input carrots found
                    {

                            fd = open("/dev/null", O_RDONLY); // input
                            if (fd == -1) // if we can't open file for reading
                            {
                                printf("Cannot open /dev/null\n");
                                fflush(stdout);
                                exit(1); 
                            }

                            if(bgFlag==1)
                            {    
                                if(DEBUG)
                                    printf("before dup2()\n");
                                fd2 = dup2(fd,0);                       // redirection of input
                                if (fd2 == -1)
                                {
                                    printf("Cannot open /dev/null\n");
                                    fflush(stdout);
                                    exit(1);
                                }
                            }
                    }

                    ////////////HANDLE OUTPUT////////////////////////
                    
                    if(outputIndex >-1)// > was found and outputIndex holds its index
                    {  
                            fd = open(args[outputIndex + 1], O_WRONLY|O_CREAT|O_TRUNC, 0644);  // output
                            if (fd == -1) // if we can't open file for writing
                            {
                                printf("Cannot open %s\n", args[outputIndex + 1]);
                                fflush(stdout);
                                exit(1); 
                            }
                            if(DEBUG)
                                printf("before dup2()\n");
                            fd2 = dup2(fd,1);                       // redirection of input
                            if (fd2 == -1)
                            {
                                printf("Cannot open %s\n", args[outputIndex+1]);
                                fflush(stdout);
                                exit(1);
                            }
                    }
                    else  // no ouput carrots found
                    {
                            fd = open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0644);
                            if (fd == -1) // if we can't open file for writing
                            {
                                printf("Cannot open /dev/null\n");
                                fflush(stdout);
                                exit(1); 
                            }
                            if(bgFlag==1)
                            {   
                                if(DEBUG)
                                    printf("before dup2()\n");
                                fd2 = dup2(fd,1);                       // redirection of input
                                if (fd2 == -1)
                                {
                                    printf("Cannot open /dev/null\n");
                                    fflush(stdout);
                                    exit(1);
                                }
                            }
                    }
                    
                    ////////////NULL TERMINATE ARGUMENTS = DON'T USE EVERYTHING AFTER CARROT///////////////
                    if(inputIndex >-1 && outputIndex>-1) // if both input/ouput carrots were present in command
                    {    
                        if(inputIndex<outputIndex)
                            args[inputIndex] = NULL;   // set carrot to NULL        
                        else
                            args[outputIndex] = NULL;   // set carrot to NULL 
                    }
                    
                    else if(inputIndex >-1)             // if only input carrot in command
                         args[inputIndex] = NULL;
                    
                    else if(outputIndex >-1)            // if only output carrot in command
                         args[outputIndex] = NULL;
                    
                    ////////////EXECUTE COMMAND////////////////////////
                    if(DEBUG)
                        printf("before execvp()\n");
                    
                    execvp(args[0], args);              // execute the command
                    
                    ////////////IF COMMAND CANNOT EXECUTE//////////////
                    printf("%s command not recognized\n", args[0]);
                    perror(" ");
                    
                    exit(1); // end child process
                    fflush(stdout);
                }
               
                ////////////IF FORK FAILED////////////////////////

                else if (cpid == -1) // unable to fork
                {   
                    printf("%s", args[0]);
                    fflush(stdout);
                    fflush(NULL);                 
                    perror(" ");
                } 
                
                ////////////WHEN WE ARE IN PARENT PROCESS////////////////////////
               
                else                
                {
                    ////////////////////////////IF PROCESS IS BACKGROUND//////////////////////////////////////
                 
                    if(DEBUG)
                        printf("in parent()\n");
                    
                    if (bgFlag ==1)                             // if process is for background process
                    {

                        printf("Background pid is %d\n", cpid); // print id of bg pid
                        fflush(stdout);

                        bgFlag = 0;                             // reset the bg flag

                        if (bgArrayCount < 1000)                // add process to background array
                        {  
                            bgArray[bgArrayCount] = cpid;
                            bgArrayCount++;
                        }
                        
                    if(DEBUG)
                        printf("%d bg processes in array\n", bgArrayCount);
                    }
                    
                    ////////////////////////////IF PROCESS IS FOREGROUND//////////////////////////////////////
                    
                    else
                    {
                        
                        fgpid = cpid;                       // assign new child process to foreground id
                    
                        
                        fgpid = waitpid(fgpid, &status, 0); // wait for fg child process to finish
                       
                        
                        sigaction(SIGINT, &ignoreSA, NULL); // activate the ignore signal handler
                        
                        if (WIFEXITED(status) )             // if process exits print status
                        {
                            sprintf(statusMessage, "exit value %d", WEXITSTATUS(status) );
                            fflush(stdout);
                        }

                        if (WIFSIGNALED(status) )           // if process terminates print status
                        {
                           sprintf(statusMessage, "terminated by signal %d\n", WTERMSIG(status) );
                           fflush(stdout);
                        }

                    }

                }
                
        }
  
        
        bgFlag = 0;      // reset background flag
        inputIndex = -1; // reset input/ouput index
        outputIndex= -1;
        
        

    }
    
    ////////////////////////////CLEANUP//////////////////////////////////////
    free(line);
    free(args);
    fflush(stdin);
    fflush(stdout);
    free(statusMessage);

    return 0;
}


/***********************************************************
 ** getArgs processes a user input and returns in a string
 ** Pre Condition: fflush(stdin)
 ** Post Condition: the receiving string holds the user input
 ***********************************************************/
char* getArgs()
{
  if(DEBUG)
      printf("In getArgs\n");
    
  char *line = NULL;
  size_t bufsize = MAX_LENGTH; // have getline allocate a buffer for us
  line = (char*)malloc(bufsize *sizeof(char));
  getline(&line, &bufsize, stdin);
  return line;
}
    
    
/****************************************************************
 ** parseLine parses a string and adds each element of the string
 ** to an array of strings. The array of strings is returned
 ** Pre Condition: string parameter must be initialized
 ** Post Condition: the receiving array holds parsed string
 ***********************************************************/
char** parseLine(char* line, int* bgFlag)
{
    if(DEBUG)
      printf("In parseLine\n");
    
    int bufsize = MAX_ARGS;                             // set limit of arguments
    char **command = malloc(bufsize * sizeof(char*));   // create an array of strings
  
    char* argument;                                     // create string
    int index = 0;                                      // create index var
    
    if(!command)                                        // ensure proper initialization
    {
        fprintf(stderr, "command not initialized correctly");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    
    argument = strtok(line, " ");                       // grab first element of string. stop and " "
    
    while(argument!=NULL)
    {
        argument[strcspn(argument, "\n")] = 0;          // strip null terminator in arg
        
        if(strcmp(argument, "&")==0)                    // if the string contains & set bgFlag to 1 to ensure processes are implemented correctly
        {
            (*bgFlag) = 1;
            argument = NULL;
        }
       
        command[index] = argument;                      // add agrument to array
        index++;
        
        argument = strtok(NULL," ");                    // grab next element. stop at " "
       
    }
    
    command[index] = NULL;                              // set last element to NULL
    
    return command;                                     // return array
}

/********************************************************************
 ** commandType deciphers what type of command user input
 ** should be considered
 ** Pre Condition: initialized array of strings as parameter
 ** Post Condition: the receiving int holds the category of command
 ** Rules: 
 ** Return 1 -> Exit Command
 ** Return 2 -> CD Command
 ** Return 3 -> Status Command
 ** Return 4 -> Comment Command
 ** Return 0 -> Non Built-In Command
 ********************************************************************/

int commandType(char** command)
{
    if(DEBUG)
    {  
        printf("In commandType\n");
        printf("First arg is: %s\n", command[0]);
    }
   
    if(strcmp(command[0], "exit") == 0)
        return 1;
    else if(strcmp("cd", command[0])==0)
        return 2;
    else if(strcmp("status", command[0])==0)
        return 3;
    else if(strcmp("#", command[0])==0)
        return 4;
    else
        return 0;
    
    
}

/********************************************************************
 ** exitCommand exits the shell script and terminates any/all 
 ** processes.
 ** Pre Condition: initialized array of PIDS as parameter and count
 ** of the number of PIDS in background array
 ** Post Condition: All processes terminated and shell exits.
 ********************************************************************/


void exitCommand(int *count, pid_t *bgArray)
{
    if(DEBUG)
      printf("In exitCommand\n");
    
    int arraycount = *count;
    fflush(stdout);
    int i;
    
    for(i=0;i<arraycount; i++)
    {
      if(DEBUG)
        printf("trying to kill bg process %d\n", i);
      kill(bgArray[i], SIGKILL); 
        
    }
    printf("Exiting all processes.\n");
    
}

/********************************************************************
 ** cdCommand changes directory based on user input
 ** Pre Condition: none
 ** Post Condition: If only "cd" is entered, directory will change
 ** to HOME directory. If invalid directory, error message will print
 ** and directory will remain unchanged.
 ********************************************************************/

void cdCommand(char** command)
{
    if(DEBUG)
      printf("In cdCommand\n");
    
    if(command[1]==NULL)            // change to home directory
        chdir(getenv("HOME"));
    
    else if(chdir(command[1])==-1)  // change directory; if directory does not exist print error.
    {
        perror("No such directory exists");
        fflush(stdout);
        
    }
}

/********************************************************************
 ** findCarrots finds redirection symbols "<" and ">" and saves
 ** their index via reference variables
 ** Pre Condition: initialized array of strings as parameter, two ints
 ** passed in as reference vars. Ints must be initialized to invalid
 ** indices such as -1.
 ** Post Condition: the references int will hold index of "<" ">"
 ** Rules:
 ** If no "<" ">" exist, the reference ints will not be changed.
 ********************************************************************/

void findCarrots(char** command, int* inputIndex, int* outputIndex)
{
    if(DEBUG)
      printf("In findCarrots\n");
    
    int i = 0;
    for( i = 0; command[i]!=NULL; i++)          // look for "<". If found set reference var to index
    {
        if(strcmp("<", command[i])==0)
        {    
            (*inputIndex) = i; 
        }
    }
    for( i = 0; command[i]!=NULL; i++)          // look for ">". If found set reference var to index
    {
        if(strcmp(">", command[i])==0)
        {    
            (*outputIndex) = i; 
        } 
    }
    
}

/********************************************************************
 ** processBgArray interates through an array of PIDs and checks to
 ** see if they have completed or not.
 ** Pre Condition: initialized array of PIDS as parameter, and int
 ** that measures the number of PIDS in array.
 ** Post Condition: If bg process has finished. This function will print
 ** the exit status via WIFEXITED or WTERMSIG
 ** After finding a finished bg process, the function removes the PID
 ** from the bgProcess array
 ********************************************************************/

void processBgArray(pid_t *bgArray, int *count)//, int* exitStatus)//, int* status)
{
    if(DEBUG)
      printf("In processBgArray\n");
    int status;
    int exitStatus;
    pid_t comCheck;
    int i;
    for(i = 0; i< (*count); i++)
    {
        comCheck = bgArray[i];
        comCheck = waitpid(comCheck, &status, WNOHANG);
        ////////////IF PROCESS COMPLETED COMCHECK != 0////////////////////////
        if(comCheck!=0)
        {
            if (WIFEXITED(status)) 
            {
                exitStatus = WEXITSTATUS(status);
                printf("Background Process with ID %d complete: Exit Value: %d.\n", bgArray[i], exitStatus);
                fflush(stdout);
            }
            else
            {
                exitStatus = WTERMSIG(status);
                printf("Background Process with ID %d complete: Termination Signal %d\n", bgArray[i], exitStatus); 
                fflush(stdout);
            }
            ////////////REMOVE PROCESS ID FROM ARRAY////////////////////////
            int j;
            for(j=i; j<(*count)-1; j++)
            {
                bgArray[j]=bgArray[j+1];
                
            }
            bgArray[(*count)-1] = INT_MAX;
            (*count)--;
        }
       
    }    
}
