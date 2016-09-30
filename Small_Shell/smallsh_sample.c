
/******************************************************************************
 ** Filename:    smallsh.c
 ** Author:      Scott Milton
 ** Date:        11/23/15
 **
 ** Description: This program is a small shell that runs command line
 **              instructions and returns results. It allows redirection of
 **              standard input and standard output and supports both
 **              foreground and background processes. The shell supports three
 **              built in commands: exit, cd, and status. It also supports
 **              comments, which are lines beginning with the # character.
 **
 ** Input:       from the keyboard: type char[]
 **              from files:        type char[]
 **
 ** Output:      to the console and files : type char[], char*, const char*, int
 ******************************************************************************/

#include <errno.h>     // for errno
#include <fcntl.h>     // for open
#include <limits.h>    // for INT_MAX
#include <signal.h>    // for sigset_t
#include <stdio.h>     // for fgets
#include <stdlib.h>    // for getenv, malloc, free
#include <string.h>    // for strcpy, strcat
#include <sys/stat.h>  // for stat 
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for waitpid
#include <unistd.h>    // for exec

#define DEBUG             0 // change to 1 for debugging print statements 
#define MAX_ARGS        512 // maximum arguments accepted on command line
#define MAX_LENGTH     2048 // maximum length for a command line
#define MAX_PIDS       1000 // maximum PIDs to track

// define bool as type
typedef enum { false, true } bool;


// declare global variables
int completed_cur = 0;
int cur = 0;                   // index to add next bg process in bgpid[]
int signalNum = 0;
pid_t bgpid[MAX_PIDS];         // array of open background process IDs
pid_t completed_pid[MAX_PIDS]; // array of completed bg process IDs
pid_t fgpid = INT_MAX;         // running foreground process



/******************************************************************************
 ** Function:          bgHandler()
 ** Description:       This function handles SIGCHLD signals. If the signal is
 **                    received from a background child process, its PID is 
 **                    stored in an array so it can be cleaned up at an
 **                    appropriate point later in the program.   
 ** Parameters:        one int: sig,
 **                    one pointer to type siginfo_t: info,
 **                    one pointer to a function: vp  
 ** Pre-Conditions:    a sigaction struct is initialized and this function is
 **                    set as the sa_sigaction value. SA_INFO must be 
 **                    included in sa_flags for the struct. completed_pid[] is
 **                    a global array of type pid_t and completed_cur is a
 **                    global variable of type INT that points to the index
 **                    to write the next PID to. fgpid is a global variable of
 **                    type INT with the PID of the current foreground child
 **                    process (if any) or set to INT_MAX otherwise    
 ** Post-Conditions:   the SIGCHLD signal has been captured and the PID of the
 **                    referring process has been added to completed_pid[] at
 **                    the index with the value of completed_cur 
 **                     
 ******************************************************************************/
void bgHandler(int sig, siginfo_t* info, void* vp);



/******************************************************************************
 ** Function:          sigintHandler()
 ** Description:       This function handles interrupt signals (SIGINT/cntl + C)
 **                    that occur while the program is running. If the signal
 **                    occurs while a foreground child process is running, the
 **                    function kills it and sets a flag so that an appropriate
 **                    message can be displayed in the main function. Signals
 **                    from other processes are ignored. 
 ** Parameters:        none
 ** Pre-Conditions:    a sigaction struct is initialized and this function is
 **                    set as the sa_handler. fgpid and signalNum are global
 **                    variables of type INT  
 ** Post-Conditions:   the SIGINT has been captured and the foreground process
 **                    (if any) has been killed  
 ******************************************************************************/
void sigintHandler();



int main(int argc, char** argv)
{
    // declare variables
    bool isBackgroundProcess = false;
    bool repeat = true;
    char *args[MAX_ARGS + 1];
    char input[MAX_LENGTH];
    char *token;
    pid_t cpid;
    int bgExitStatus;
    int bgStatus; 
    int exitStatus;
    int fd;
    int fd2;
    int i;
    int j;
    int numArgs;
    int status;

    // create instance of sigaction struct for background processes
    struct sigaction background_act;
    background_act.sa_sigaction = bgHandler;     
    background_act.sa_flags = SA_SIGINFO|SA_RESTART;
    sigfillset(&(background_act.sa_mask));
    // set up signal handler for completed child process
    sigaction(SIGCHLD, &background_act, NULL);

    // create instance of sigaction struct for foreground processes
    struct sigaction foreground_act;
    foreground_act.sa_handler = sigintHandler;
    foreground_act.sa_flags = SA_RESTART;
    sigfillset(&(foreground_act.sa_mask));
    sigaction(SIGINT, &foreground_act, NULL); 

    // create sigaction struct to ignore interrupts the rest of the time
    struct sigaction restOfTheTime_act;
    restOfTheTime_act.sa_handler = SIG_IGN;
    restOfTheTime_act.sa_flags = SA_RESTART;
    sigfillset(&(restOfTheTime_act.sa_mask));
    sigaction(SIGINT, &restOfTheTime_act, NULL); 

    // initialize arrays for bg processes
    for (i = 0; i < MAX_PIDS; i++)
    {
        completed_pid[i] = bgpid[i] = INT_MAX;
    }   

    // allocate memory for arg array
    for (i = 0; i <= MAX_ARGS; i++)
    {
        args[i] = (char *) malloc((MAX_LENGTH + 1) * sizeof(char)); 
    }  

    do
    {
        // create array of pointers to the strings in the arg array
        char **next = args;

        // (re)initialize the argument array
        for (i = 0; i <= MAX_ARGS; i++)
        {
            strcpy(args[i], "\n");
        }

        // clear input buffer each iteration
        strcpy(input, "\0");
 
        i = 0;

        // this loop cleans up zombies, waiting for all ps in completed array
        while (i < MAX_PIDS && completed_pid[i] != INT_MAX)
        {
            if (DEBUG) 
            {
                printf("Now cleaning up process %d\n", completed_pid[i]);
            }

            // wait on current process
            completed_pid[i] = waitpid(completed_pid[i], &bgStatus, 0);

            // print process id and exit status
            
            if (WIFEXITED(bgStatus)) 
            {
                bgExitStatus = WEXITSTATUS(bgStatus);
                printf("background pid %d is done: exit value %d.\n", completed_pid[i], bgExitStatus);
            }
            else
            {
                bgExitStatus = WTERMSIG(bgStatus);
                printf("background pid %d is done: terminated by signal %d\n", completed_pid[i], bgExitStatus);
 
            }

            // remove current ps from open background process array
            j = 0;
            while (j < MAX_PIDS && bgpid[j] != INT_MAX)
            { // cycle through array of bg processes
                // and look for match 
                if (bgpid[j] == completed_pid[i])
                {
                    if (DEBUG)
                    {
                        printf("Now removing process %d from array.\n", bgpid[j]);
                    }                   

                    // replace value of current bg process 
                    bgpid[j] = INT_MAX;
 
                    // shift all subsequent PIDs down to fill `gap`
                    int k = j;                       
                    while (k + 1 < MAX_PIDS && bgpid[k+1] != INT_MAX)
                    {
                        bgpid[k] = bgpid[k+1];
                        bgpid[k+1] = INT_MAX;
                        k++;
                    }    
                    // adjust cur index value & make room for new PID  
                    cur--; 
                }
                // increment counter
                j++;
            }

            // replace value of current completed process
            completed_pid[i] = INT_MAX;

            // increment counter
            i++; 
        }

        // reset completed bg process array index tracker
        completed_cur = 0;

        // flush out prompt each time it is printed
        fflush(stdin);
        fflush(stdout);

        // prompt user for input
        printf(": ");

        // get user input
        fgets(input, MAX_LENGTH, stdin);

        // flush out prompt
        fflush(stdin);

        // check for blank lines, and NULL
        if (input[0] == '\n' || input[0] == '\0')
        {
            continue;
        }
 
        // process and parse input
        numArgs = 0;
        token = strtok(input, " "); // check for multiple args

        if (DEBUG)
        {
            printf("token is %s\n", token); 
        }

        // loop to process args (up to 512)
        while (token != NULL && numArgs < MAX_ARGS)  
        {
 
            // this serves to ignore leading / duplicate / trailing spaces 
            if (strlen(token) == 0)
            {
                continue;
            }   

            if (DEBUG)
            {
                printf("overwriting %s with %s\n", *next, token);
            }

            // copy current arg to arg array
            strcpy(*next, token);

            if (DEBUG)
            {
                printf("args[%d] is: %s\n", numArgs, args[numArgs]); 
            }

            // increment argument  counter
            numArgs++;
 
            // get next arg, if any
            token = strtok(NULL, " ");

            // increment pointer unless last iteration
            if (token != NULL)
            {
                *next++;
            } 
        }

        if (DEBUG)
        {
            printf("overwriting %s", *next);
        }

        // remove newline char from last arg, if any
        token = strtok(*next, "\n"); 
        if (token != NULL)
        {
            strcpy(*next, token);
        }

        if (DEBUG)
        {
            printf(" with %s\n", *next);
            printf("args[%d] is: %s\n", numArgs - 1, args[numArgs - 1]); 
        }

        // if command is bg process
        if (strcmp(args[numArgs - 1], "&") == 0)
        {
            // set variable appropriately for later 
            isBackgroundProcess = true;

            // decrement number of args since ampersand will be removed
            numArgs--; 

            // do not increment pointer so that ampersand is removed  
        }
        else
        {
            // increment pointer
            *next++;
        }

        if (DEBUG)
        {
            printf("overwriting %s with NULL\n", *next);
        }

        if (strncmp(args[0], "#", 1) == 0)
        {
            // do nothing for comments
        }
        else if (strcmp(args[0], "exit") == 0)
        {

            // kill any processes or jobs that shell has started
            i = 0;
            while (i < MAX_PIDS && bgpid[i] != INT_MAX)
            {
                if (DEBUG)
                {
                    printf("Now killing process %d\n", bgpid[i]);
                }
 
                kill(bgpid[i], SIGKILL);
                i++;
            }

            // free allocated memory
            for (i = 0; i <= MAX_ARGS; i++)
            {
                if (DEBUG)
                {
                    printf("Now freeing memory for args[%d], which has a value of %s\n",i, args[i]);
                } 
                free(args[i]); 
            }  

            // exit the shell
            repeat = false;

        }
        else if (strcmp(args[0], "cd") == 0)
        { // change working directories

            // if no args, change to directory specified in HOME env var
            if (numArgs == 1)
            {
                chdir(getenv("HOME"));
            }
            // if one arg, change to dir provided
            else
            {
                chdir(args[1]);
            }
            // support absolute and relative paths
        }
        else if (strcmp(args[0], "status") == 0)
        { // print exit status or terminating signal of last fg command

            if (WIFEXITED(status))
            {
                exitStatus = WEXITSTATUS(status);
                printf("exit value %d\n", exitStatus);
            }
            else if (signalNum != 0)
            {
                printf("terminated by signal %d\n", signalNum);
            } 

        }
        else // pass through to BASH to interpret command there
        {
            // need fork and exec
            cpid = fork(); // fork off the parent process

            if (cpid == 0) // child process
            {
                bool checkStatus = false; 
                bool redirectInput = false;
                bool redirectOutput = false;
                int inputOffset = 0; // which index to we reference for input redirections
                int outputOffset = 0; //which index to we reference for output redirection

                if (numArgs > 4 && strcmp(args[numArgs-4], "<") == 0) // WHEY GREATER THAN FOUR????
                {
                    if (DEBUG)
                    {
                        printf("1) input redirected to %s\n", args[numArgs-3]);     
                    }

                    // set flag to redirect input
                    redirectInput = true; // we know we want to redirect input

                    // set target for input path
                    inputOffset = 3;  // get us to argument we want to input to
                }
                else if (numArgs > 2 && strcmp(args[numArgs-2], "<") == 0)// WHEY GREATER THAN TWO????
                {
                    if (DEBUG)
                    {
                        printf("2) input redirected to %s\n", args[numArgs-1]);     
                    }

                    // set flag to redirect input
                    redirectInput = true;

                    // set target for input path
                    inputOffset = 1; 
                }
                if (numArgs > 4 && strcmp(args[numArgs-4], ">") == 0) // we want to do output
                {
                    if (DEBUG)
                    {
                        printf("3) output redirected to %s\n", args[numArgs-3]);     
                    }
 
                    // set flag to redirect output
                    redirectOutput = true;

                    // set target for output path
                    outputOffset = 3; 
                }
                else if (numArgs > 2 && strcmp(args[numArgs-2], ">") == 0)
                {
                    if (DEBUG)
                    {
                        printf("4) output redirected to %s\n", args[numArgs-1]);     
                    }
 
                    // set flag to redirect output
                    redirectOutput = true;

                    // set target for output path
                    outputOffset = 1; 
                }

                // redirect stdin for bg process to dev/null if no path provided
                if (isBackgroundProcess == true && redirectInput == false)
                {
                    fd = open("/dev/null", O_RDONLY);

                    checkStatus = true;      
                }
                else if (redirectInput == true)
                {
                    fd = open(args[numArgs - inputOffset], O_RDONLY);

                    checkStatus = true;  
                }

                if (checkStatus == true) // checkStatus is for checking status of opened file
                {
                    if (fd == -1) // if we can't open file for reading
                    {
                        printf("smallsh: cannot open %s for input\n", args[numArgs - inputOffset]);
                        exit(1); 
                    }

                    fd2 = dup2(fd, 0); //dumping stdin to where fd points 
                    if (fd2 == -1)
                    {
                        printf("smallsh: cannot open %s for input\n", args[numArgs - inputOffset]);
                        exit(1);
                    }   
                }

                if (redirectOutput == true)
                {
                    fd = open(args[numArgs - outputOffset], O_WRONLY|O_CREAT|O_TRUNC, 0644);

                    if (fd == -1)
                    {
                        printf("smallsh: cannot open %s for output\n", args[numArgs - outputOffset]);
                        exit(1); 
                    }

                    fd2 = dup2(fd, 1); //dump standard output to where fd points
                    if (fd2 == -1)
                    {
                        printf("smallsh: cannot open %s for output\n", args[numArgs - outputOffset]);
                        exit(1);
                    }   
                }

                // get the greater of the offsets, if any
                i = 0;
                if (inputOffset > outputOffset)
                {
                    i = inputOffset + 1;
                }
                else if (outputOffset > inputOffset)
                {
                    i = outputOffset + 1;
                }

                // move the pointer to omit the input redirection from array
                for (j = i; j > 0; j--)
                {
                    *next--;
                }

                // add NULL pointer to last array index (only in child)
                *next = NULL;

                // exec using path version in order to use Linux built-ins
                execvp(args[0], args);

                // this will never run unless error (i.e.- bad filename)
                printf("%s", args[0]);
                fflush(NULL);
                perror(" ");  
 
                exit(1); // end child process
            }
            else if (cpid == -1) // parent process
            {   
                // if unable to fork print error
                printf("%s", args[0]);
                fflush(NULL);                 
                perror(" ");
            } 
            else
            {
                // parent process continues here

                // if command is bg process
                if (isBackgroundProcess == true)
                {
                    // then print process id when begins
                    printf("background pid is %d\n", cpid);

                    // reset boolean value for next iteration
                    isBackgroundProcess = false;

                    // add process id to array of background processes
                    if (cur < MAX_PIDS)
                    {  
                        bgpid[cur++] = cpid;
                    }
                } 
                else
                {
                    // reset value of signal number
                    signalNum = 0;                     

                    // assign cpid to global variable
                    // for access in signal handlers  
                    fgpid = cpid;

                    // set interrupt handler for fg process 
                    sigaction(SIGINT, &foreground_act, NULL);

                    // wait for fg child process
                    fgpid = waitpid(fgpid, &status, 0);

                    // restore to ignore interrupts
                    sigaction(SIGINT, &restOfTheTime_act, NULL);

                    // reset global variable so signal handlers know
                    // there is no active fg process
                    fgpid = INT_MAX;

                    // if process was terminated by signal, print message
                    if (signalNum != 0)
                    {
                        printf("terminated by signal %d\n", signalNum);
                    }   
                }
            }
        }

    } // repeat until user exits shell
    while(repeat == true);

    return 0;
}



void bgHandler(int sig, siginfo_t* info, void* vp)
{
    if (DEBUG)
    {
        printf("In bgHandler.\n");
    }

    pid_t ref_pid = info->si_pid; 

    // if signal is not from fg process, process it here
    if (ref_pid != fgpid && completed_cur < MAX_PIDS)
    {
        // add to completed bg process array so message can
        // be displayed in main loop
        completed_pid[completed_cur++] = ref_pid;
    } 

    return;
}



void sigintHandler()
{
    // if interrupt signal occurs while fg process is running, kill it
    if (fgpid != INT_MAX)
    {
        // kill the foreground process
        kill(fgpid, SIGKILL);
 
        // set global variable for status messages
        signalNum = 2;  
    }  

    // ignore interrupt signal for all other processes
    // and simply return
    return;
}
