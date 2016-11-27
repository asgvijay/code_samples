// ftserver.c
// Vijay Kumar
// Program 2

#include <stdio.h>  // Manipulate file and I/O streams: printf(), fprintf(), sprintf(),fputs(), fgets(), etc...
#include <stdlib.h> // atoi(), exit(), qsort(), rand(), etc...
#include <string.h> // strncat(), strcmp(), strncpy(), strlen(), strtok(), etc...
#include <dirent.h> // To use the DIR type. Includes: closedir(), opendir(), readdir(), etc...
#include <unistd.h> // PID, Signals, and Process Management
#include <sys/stat.h> // chmod(), mkdir(), mkfifo(), stat(), etc...
#include <time.h> // asctime(), clock(), time(), etc...
#include <assert.h> // assert(int expression)
#include <sys/wait.h> // used to wait for processes
#include <sys/types.h> // to work with file redirection
#include <fcntl.h> // to open files and redirect streams 
#include <signal.h> // To catch and react to signals
#include <sys/socket.h> // to use sockets
#include <netinet/in.h> // to work with ip
#include <netdb.h>

int daemonSetup(int portno);
int dataSocketSetup(int portno, char hostName[]);
void receiveCommand(char command[], int sockfd);
char* processCommand(char command[], int* dPort);
void sendFile(char* pCommand, int* dPort, char hostName[]);
void getDirectory(char directory[]);


 int DEBUG = 0;

int main(int argc, char* argv[])
{
    
    
    
    // Ensure proper number of arguments 
    if(argc<2)
    {
        perror("ftpserver : incorrect number of agruments");
        exit(1);
    }
    
    
       
    char command[1024];  // buffer to store command
    bzero(command, 1024);
    char* pCommand;     // buffer to store the parsed command
    char *source = NULL; // buffer to store file that is to be sent
    FILE* openFile; // file pointer for opening file to be sent
    int* dPort;     // data port 
    char* fComing = "Receiving File from Server";
    char* noExist = "This file does not exist";
    char* invalidCommand = "Invalid Command";
    int n;
    char directory[1024]; // string to hold directory listing
    dPort = malloc(sizeof(int)); 
    struct sockaddr_in cliAddr; // struct to hold details of client connection
    socklen_t cliLen=sizeof(struct sockaddr);
    char clientAddress[256];
    int clientSock; 

    // create socket for connections
    int sockfd = daemonSetup(atoi(argv[1]));
	signal(SIGCHLD, SIG_IGN);
 
    
    // This loop runs until quit by using control-c
    while(1)
    {
        
        // Accept a connection
        printf("Server open on port: %d\n", atoi(argv[1]));
        clientSock = accept(sockfd,(struct sockaddr *) &cliAddr, &cliLen);
        if (clientSock==-1)
                perror("accept call failed");
        else
            printf("Connected with client.\n");
        
        // Get details about client we are connected to
        inet_ntop(AF_INET, &(cliAddr.sin_addr), clientAddress, 17);
        
        printf("Hostname is: %s\n", clientAddress);
        printf("Connection from client on port: %d\n", atoi(argv[1]));
        
        // received the command from client
        receiveCommand(command, clientSock);
        
        // process the command
        pCommand = processCommand(command, dPort);

    
        // See what processCommand() returned and handle accordingly
        // Invalid Command - sends client a "Invalid Command" message
        // Print List - sends client a listing of all files in directory
        // Else Statement - Sees if requested file exists and sends if found
        
        if(strcmp(pCommand, "Invalid Command")==0)
            n = send(clientSock,invalidCommand,strlen(invalidCommand),0);
            if(n < 0)
                perror("ERROR writing to socket");

        else if(strcmp(pCommand, "Print List")==0)
        {
            getDirectory(directory);
            printf("Sending directory to client.\n");
            n = send(clientSock,directory,strlen(directory),0);
            if(n < 0)
                perror("ERROR writing to socket");
            bzero(directory, 1024);
        }

        //http://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
        // line of code to see if file exists borrowed from this link
        else 
        {
        
            if( access(pCommand, F_OK ) != -1 ) {

                // file exists
                n = send(clientSock,fComing,strlen(fComing),0);
                sendFile(pCommand, dPort, clientAddress);
            } else {
                // file doesn't exist
                printf("Sending File Not Found message to client.\n");
                n = send(clientSock,noExist,strlen(noExist),0);
            }


        }

        
        // Clean things up before looping again/
        fflush(stdout);
        bzero(command,1024);
        bzero(clientAddress, 256);
    
    }
    
    // Close socket
    close(sockfd);                        

return 0;

}

///////////////////////////////////////////////
// deamonSetup prepares the server socket and
// allows the server to listen for 1 connection
// The socket ID is returned
///////////////////////////////////////////////

int daemonSetup(int portno)
{
    if(DEBUG)
        printf("in daemonSetup\n");
    
    int sockfd;
    struct sockaddr_in server;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("socket");
        exit(1);
    }
  
    bzero((char *) &server, sizeof(server));
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &server,sizeof(server))==-1)
        perror("ERROR on binding");
    
	if(listen(sockfd,1)==-1)
    {
        perror("listen call failed");
        exit(1);
        
    }
	//printf("the sockfd in deamon is: %d", sockfd);
    
    return sockfd;
    
}


///////////////////////////////////////////////
// receivedCommand takes an empty char array and
// socket ID as arguments.
// This function receives the message sent by the
// client. The empty char array is filled with a 
// string representing the command sent by client.
// The char array is returned.
///////////////////////////////////////////////

void receiveCommand(char command[], int sockfd)
{
    
    if(DEBUG)
        printf("in received Command\n");
    
    char buffer [256];
  	
    int n;
    int loop = 1;
  
    n = recv(sockfd,buffer,256,0);
    if (n < 0)             
        perror("ERROR reading from socket in daemon");
        
    strcat(command, buffer);
    
    command[strcspn(command, "\n")] = 0;
    strcat(command, "\0");
  
        
    bzero(buffer,256);	                             
}


///////////////////////////////////////////////
// processCommand takes a char array and pointer
// to an integer.
// The array must contain a string that represents
// the command sent by the client. 
// The command is processed and the client's 
// requested data port is assigned to the integer
// pointer. The function ultimately returns a
// string.
// Return value of "Print List" means we send 
// client directory.
// Return value of "Invalid Command" means we 
// send client an error
// Return value with a filename means we attempt
// to send the file
///////////////////////////////////////////////

char* processCommand(char command[], int* dPort)
{
    if(DEBUG)
        printf("in process Command\n");


    if(strncmp(command, "-l", 2)==0 )
    {
        // if command is list
        // send list of files in directory to clien
        return "Print List";
        
    }
    else if(strncmp(command, "-g", 2)==0 )
    {
        // if command is "get"
        // get file name
        char* delimeter =  " ";
        char* fileName = strtok(command, delimeter);
        //printf("fileName is %s: \n", fileName);
        fileName = strtok(NULL, " ");
        //printf("fileName is %s: \n", fileName);
        char* dataPort = strtok(NULL, " "); 
        *dPort = atoi(dataPort);
        //printf("dataPort is %d: \n", (*dPort));
        return fileName;
        
    }
    
    else
    {
        
        // send message that tells client "Invalid Command....";
        return "Invalid Command";
        
    }
    
    
}

///////////////////////////////////////////////
// sendFile
// preCondition: pCommand must hold name of file
// preCondition: dPort must point to the clients 
// data port identifier
// preCondition: hostName must hold valid client
// hostName
// PostConditions: Server sends file to client
// via client established port number or sends
// error message saying file not found
///////////////////////////////////////////////
                             
void sendFile(char* pCommand, int* dPort, char hostName[])
{
    
    //http://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c
        // search for file in directory
        FILE* openFile;
        openFile = fopen(pCommand, "r");
        char* source; 
    
        if(openFile!=NULL)
        {
            
            printf("File found: %s: \n", pCommand);
            /* Go to the end of the file. */
            if (fseek(openFile, 0L, SEEK_END) == 0) 
            {
                /* Get the size of the file. */
                long bufsize = ftell(openFile);
                if (bufsize == -1) 
                { printf("incompatible file");
                    exit(0);                   

                                   }

                /* Allocate our buffer to that size. */
                source = malloc(sizeof(char) * (bufsize + 1));

                /* Go back to the start of the file. */
                if (fseek(openFile, 0L, SEEK_SET) != 0) { /* Error */ }

                /* Read the entire file into memory. */
                size_t newLen = fread(source, sizeof(char), bufsize, openFile);
                if ( ferror( openFile ) != 0 ) {
                    fputs("Error reading file", stderr);
                } else {
                    source[newLen++] = '\0'; /* Just to be safe. */
                }
                
                
                // make connection
                //printf("dPOrt is: %d\n", *dPort);
                int dataSocket = dataSocketSetup(*(dPort), hostName);
                printf("Sending %s to %s. \n", pCommand, hostName);
                int n = send(dataSocket,source,bufsize,0);
                if(n < 0)
                    perror("ERROR writing to socket");
                close(dataSocket);  
            }
            
            fclose(openFile);
            
        }
    
        else    
            printf("no file matches that name.\n");
        

        free(source);
          
            
    
}
    
///////////////////////////////////////////////
// dataSocketSetup
// preCondition: portNo must hold client requested
// data port
// preCondition: hostName must hold valid client
// hostname
// PostConditions: New connection is made with
// current client on requested port 
// Returns the ID of the socket
///////////////////////////////////////////////
                             
int dataSocketSetup(int portno, char hostName[])
{
    int sockfd;
    
    struct sockaddr_in server;
    struct hostent *hostIP = gethostbyname(hostName); 
    if (hostIP == NULL)
        perror("Error: could not resolve server host name.\n");
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {   
        perror("socket failure");
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);
    memcpy(&server.sin_addr, hostIP->h_addr, hostIP->h_length);
    
    if(connect(sockfd, (struct sockaddr *) &server, sizeof(server)) ==-1)
    {
        perror("connection error");
        exit(1);
        
    }
    
    return sockfd;
    
}                           
  

///////////////////////////////////////////////
// getDirectory
// preCondition: empty char array as argument
// postCondition: the char array is filled with 
// a string containing the listing of files in
// the current directory
///////////////////////////////////////////////
                             
                           
//http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1046380353&id=1044780608
void getDirectory(char directory[])
{
    
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        strcat(directory, "File Listing:\n");
        while ((dir = readdir(d)) != NULL)
        {
            //printf("%s\n", dir->d_name);
            strcat(directory, dir->d_name);
            strcat(directory, "\n");
        }
        closedir(d);
    }
    
}















                             
                             