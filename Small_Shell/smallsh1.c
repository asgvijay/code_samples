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

char* getArgs();
char** parseLine(char* line, int* bgFlag);
void processBgArray(pid_t *bgArray, int *count);//, int* exitStatus);//, int* status);
void findCarrots(char** command, int* inputIndex, int* outputIndex);
void cdCommand(char** command);
void exitCommand(int *count, pid_t *bgArray, char* line, char** args, int *again);
int commandType(char** command);
pid_t cpid;
pid_t fgpid;
int fd;
int fd2;

int main()
{
    // set up sigaction structures
    struct sigaction defaultSA;
    struct sigaction ignoreSA;
    ignoreSA.sa_handler = SIG_IGN;
    defaultSA.sa_handler = SIG_DFL;
    int again = 1;
    //int testpid;
    
    char* line;                                     // string to hold user input
    line = (char*)malloc(MAX_LENGTH *sizeof(char)); // initialize
    if(!line)                                       // ensure line initializes correctly
    {
        fprintf(stderr, "allocation error");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    char** args = malloc(MAX_ARGS *sizeof(char*));  // array of strings to hold parsed command
    if(!args)                                       // ensure args initializes correcty
    {
        fprintf(stderr, "allocation error");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    pid_t bgArray[1000];                         // array to hold background pids
    int bgArrayCount = 0;                       // count measuring how many pids in array
    int bgFlag = 0;                             // flag for testing if command is for bg process
    int status = 0;                             // holds status or last process
    int commandtype;                            // var for measuring what type of command input is
    int inputIndex = -1;                        // var to hold the index of redirection carrots
    int outputIndex = -1;
    //int signalNum;
    int exitStatus;                             // var to aid in error messaging
    char* statusMessage = malloc(100* sizeof(char));    // string to hold status message
    if(!statusMessage)                                       // ensure status message initializes correcty
    {
        fprintf(stderr, "allocation error");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    
    // do while loop to run core of shell
    do
    {
        fflush(stdout);    
        fflush(stdin);
        processBgArray(bgArray, &bgArrayCount); //process any background pid
        printf(": ");                           // print colon
        fflush(stdout);                         // flush stdout
        line = getArgs();                       //get line from arguments
        fflush(stdin);
        args = parseLine(line, &bgFlag);        //break up line into its constituent parts
        //free(line);
        commandtype = commandType(args);        // decipher what type of command input is (built-in or exec)
    
    
        if(commandtype ==1)    
        {  
            if(DEBUG)
                    printf("before exitCommand()\n");
                
                exitCommand(&bgArrayCount, bgArray, line, args, &again); // exit current process
                again = 0;
                exit(0);
                //break;
        }
        else if(commandtype == 2) 
        {     
            if(DEBUG)
                printf("before cdCommand()\n");
            cdCommand(args);                // change to appropriate directory
               
        }
    
        else if(commandtype == 3)
        {
            printf("%s\n", statusMessage);  // print the most recent status message
            fflush(stdout);
                
        }
            
        else if(commandtype == 4)  
                printf("do nothign");
            
     
        else
        {
            if(DEBUG)
                    printf("before fork()\n");
                
                cpid = fork();                  // fork the current process
                printf("The cpid after fork is: %d\n", cpid);
                ////////////WHEN WE ARE IN CHILD PROCESS////////////////////////
                
                if(cpid ==0) // in child process
                {
                    if(!bgFlag)
                        sigaction(SIGINT, &defaultSA, NULL); // set interrupt handler for fg process 
                    
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
                 
                    if(DEBUG)
                        printf("in parent()\n");
                    
                    if (bgFlag ==1)
                    {

                        printf("Background pid is %d\n", cpid); // print id of bg pid
                        fflush(stdout);

                        bgFlag = 0;                             // reset the bg flag

                        if (bgArrayCount < 1000)
                        {  
                            bgArray[bgArrayCount] = cpid;
                            bgArrayCount++;
                        }
                    if(DEBUG)
                        printf("%d bg processes in array\n", bgArrayCount);
                    } 
                    
                    else
                    {
                        
                        fgpid = cpid;
                       // printf("my fgpid is: %d\n", fgpid);
                        //printf("my fgpid should be: %d\n", getpid());
                        // wait for fg child process
                        fgpid = waitpid(fgpid, &status, 0);
                        //testpid = waitpid(fgpid, &status, 0);
                        // restore to ignore interrupts
                        sigaction(SIGINT, &ignoreSA, NULL);
                        
                        if (WIFEXITED(status) ) 
                        {
                            sprintf(statusMessage, "exit value %d", WEXITSTATUS(status) );
                            fflush(stdout);
                        }

                        if (WIFSIGNALED(status) ) 
                        {
                           sprintf(statusMessage, "terminated by signal %d\n", WTERMSIG(status) );
                           fflush(stdout);
                        }
                        

                        // reset global variable so signal handlers know
                        // there is no active fg process
                        //fgpid = INT_MAX;

                        // if process was terminated by signal, print message
                        if (status != 0)
                        {
                            printf("terminated by signal %d\n", status);
                            fflush(stdout);
                        }   
                    }

                }
               
            
                
        }
  
                
        bgFlag = 0;       
        inputIndex = -1; // reset input/ouput index
        outputIndex= -1;
       
        

    }while(again);
    
free(line);
free(args);
fflush(stdin);
fflush(stdout);
free(statusMessage);
return 0;
}


// Get the user input (Command) 

/*******************************
** Get the command line string
*******************************/
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
    
    

// Parse the input into usable information 
// if bgFlag is set to 1, we know command is for bg process
char** parseLine(char* line, int* bgFlag)
{
    if(DEBUG)
      printf("In parseLine\n");
    
    int bufsize = MAX_ARGS;
    char **command = malloc(bufsize * sizeof(char*));
  
    char* argument;
    int index = 0;
    
    if(!command)
    {
        fprintf(stderr, "allocation error");
        fflush(stdout);
        exit(EXIT_FAILURE);
        
    }
    
    argument = strtok(line, " ");
    
    while(argument!=NULL)
    {
        argument[strcspn(argument, "\n")] = 0;          // strip null terminator in arg
        
        if(strcmp(argument, "&")==0)
        {
            (*bgFlag) = 1;
            argument = NULL;
        }
       
        command[index] = argument;
        index++;
        
        argument = strtok(NULL," ");
       
    }
    
    command[index] = NULL;
    
    return command; 
}

// Decipher what the command is
// return 1 if exit command
// return 2 if cd command
// return 3 if status command
// return 0 if not built in command

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

// Process exit command

void exitCommand(int *count, pid_t *bgArray, char* line, char** args, int* again)
{
    if(DEBUG)
      printf("In exitCommand\n");
    
    int arraycount = *count;
    printf("array count = %d\n", arraycount);
    fflush(stdout);
    int i;
    
    for(i=0;i<arraycount; i++)
    {
      if(DEBUG)
        printf("trying to kill bg process %d\n", i);
      kill(bgArray[i], SIGKILL); 
        
    }
    printf("Exiting all processes.\n");
    again = 0;          
}

// Process cd command

void cdCommand(char** command)
{
    if(DEBUG)
      printf("In cdCommand\n");
    
    if(command[1]==NULL)
        chdir(getenv("HOME"));
    else if(chdir(command[1])==-1)
    {
        perror("No such directory exists");
        fflush(stdout);
        
    }
}

// find carrots in command
// if function returns -1, no carrot found, no redirection necessary
// if input direction is found carrotTest = 0
// if output direction is found carroTest = 1
// returns index of character

void findCarrots(char** command, int* inputIndex, int* outputIndex)
{
    if(DEBUG)
      printf("In findCarrots\n");
    
    int i = 0;
    for( i = 0; command[i]!=NULL; i++)
    {
        if(strcmp("<", command[i])==0)
        {    
            (*inputIndex) = i; 
        }
    }
    for( i = 0; command[i]!=NULL; i++)
    {
        if(strcmp(">", command[i])==0)
        {    
            (*outputIndex) = i; 
        } 
    }
    
}


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
