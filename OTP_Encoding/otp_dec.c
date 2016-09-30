// otp_enc.c
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


int fileSizeCmp(char encodeText[], char keyText[]);
int clientSocket(int portno);
void estConnection(int sockfd, char* message);
void sendTextFile(char text[], int sockfd);
void receiveCipher(char cipherText[], int sockfd);
#define DEBUG 0


int main(int argc, char* argv[])
{
    
    if(argc <3)
    {
        perror("otp_enc.c : too few arguments");
        exit(1);
    }
    
    FILE *cipherText;                               // create file pointers
    FILE *keyText;
    
    cipherText = fopen(argv[1], "r");               // open files for reading
    keyText = fopen(argv[2], "r");
        
    if(cipherText ==NULL || keyText == NULL)
    {
        perror("otp_enc.c : bad files as arguments");
        exit(1);
    }
    
    char decText[70000];                               // create buffers and read files into them
    char kText[70000];
    
    bzero(decText,70000);
    bzero(kText,70000);
    
    fgets(decText,70000,cipherText);
    fgets(kText,70000,keyText);
    
    if(fileSizeCmp(decText, kText))
    {
        perror("otp_enc.c : keyText file not big enough");
        exit(1);
    }
    int sockfd = clientSocket(atoi(argv[3]));         // set up socket for client
   
    estConnection(sockfd, "decAck");                  // establish connection with server
     
    sendTextFile(decText, sockfd);                    // send files to server
    sendTextFile(kText, sockfd);
    
    char originalText[70000];                           // receive cipher text back from server
 
    bzero(originalText,70000);
    receiveCipher(originalText, sockfd);
    
    
    close(sockfd);

	printf("%s\n", originalText);                       // print original plain text

    return (0); 
}


/***************************************************
 ** fileSizeCmp compares the length of two c strings
 ** parameters: 2 c strings
 ** preconditions: two initialized c strings
 ** post condition: returns 1 if key is not big enough
 ** returns 0 if key is big enough
 ***************************************************/

int fileSizeCmp(char encodeText[], char keyText[])
{
    
    if(DEBUG)
    {
        printf("In FILESIZECMP\n");
        fflush(stdout);
    }
    
    int i;
    
    for(i=0; i<strlen(encodeText); i++)     // loop through all chars in encode text ensuring keyText has a valid char at that index

    {
        
        if(keyText[i] == '\n' || keyText[i] == '\0')
            return 1;
        
    }
    return 0;
    
}

/***************************************************
 ** clientSocket sets up the socket to comm with
 ** server.
 ** parameters: one int, representing the portno
 ** preconditions: valid portno
 ** post condition: socket is opened and connected
 ** to server at specified port number.
 ***************************************************/

int clientSocket(int portno)
{
    if(DEBUG)
    {
        printf("In _DEC CLIENTSOCKET\n");
        fflush(stdout);
    }
    
    int sockfd;
    
    struct sockaddr_in server;                              // create server struct
    struct hostent *hostIP = gethostbyname("localhost");    // create host struct - assign localhost
    if (hostIP == NULL)
    {
        perror("Error: could not resolve server host name.\n");
        exit(1);
    }
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)    // open socket
    {   
        perror("otp_enc.c : socket failure");
        exit(1);
    }
    
    // set up server
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);
    memcpy(&server.sin_addr, hostIP->h_addr, hostIP->h_length);
    
    if(connect(sockfd, (struct sockaddr *) &server, sizeof(server)) ==-1)
    {
        perror("connection error");
        exit(1);
        
    }
    
    return sockfd;                                          // return id of socket
    
}

/*******************************************************
 ** estConnection establishes connection with server
 ** parameters: socket id, c string
 ** preconditions: valid socket id, initialize c string
 ** post condition: client is properly communicating with
 ** server.
 ******************************************************/
void estConnection(int sockfd, char* message)
{
    if(DEBUG)
    {
        printf("In _DEC ESTCONNECT\n");
        fflush(stdout);
    }
    
    char buffer[256];                       // buffer for message
    memset(buffer, '\0', sizeof(buffer));   // copy message to buffer
    strcpy(buffer, message);
    
    ssize_t n;
    
    n = send(sockfd, buffer, 255, 0);       // send message to server
    if(n<0)
    {  
        perror("send error");
        exit(1);
    
    }

    n=0;
    memset(buffer, '\0', sizeof(buffer));
    
    n = recv(sockfd, buffer, 255, MSG_WAITALL); // receive message from server
    if(n<0)
    {  
        perror("receive error");
        exit(1);
    
    }

    buffer[strcspn(buffer, "\n")] = 0;
    
    if(strcmp(message, buffer))                 // if message isn't identical then we close
    {  
        close(sockfd);
        perror("Bad Auth: cannot use otp_enc_d");
        exit(1);
    
    }
}

/***************************************************
 ** sendTextFile sends string to server
 ** parameters: c string and int
 ** preconditions: initialized c string and valid
 ** socket id
 ** post condition: server has received the message
 ** or error is thrown
 ***************************************************/

void sendTextFile(char text[], int sockfd)
{
    if(DEBUG)
    {
        printf("IN _DEC SEND TEXT FILE\n");
        fflush(stdout);
    }
    
    
    char buffer[70000];                          // set up buffer
    memset(buffer, '\0', sizeof(buffer));       // clear buffer
    int n;                                      // var for error checking
    
    strcpy(buffer, text);                       // copy text to buffer
    
    if (DEBUG)
    {
        printf("otp_enc : reading input file: %s\n", buffer);
        fflush(stdout);
    }
    
    n = send(sockfd,buffer,70000, 0);           // send text to server
    
    if(n < 0)                                   // error checking
    {
        perror("ERROR writing to socket");
        exit(1);
        
    }
    if(DEBUG)
    {
        printf("otp_enc: sendTextFile() :Successfull Send\n");
        fflush(stdout);
    }
    
    memset(buffer, '\0', sizeof(buffer));        // clear buffer
    n = recv(sockfd,buffer,255,MSG_WAITALL);    // receive acknowledgment from server
    
    if (n < 0)                                  // error checking
    {
        perror("ERROR writing to socket");
        exit(1);
        
    }
    if(DEBUG)
    {
        printf("otp_enc: sendTextFile() :Successfull Receive\n");
        fflush(stdout);
    }
    
    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer,"exit");
    
    n = send(sockfd,buffer,70000,0);                // send exit to server
    
    if(n < 0)                                       // error checking
    {
        perror("ERROR reading to socket");
        exit(1);
        
    }
    if(DEBUG)
    {
        printf("otp_enc: sendTextFile() :Exit command sent\n");
        fflush(stdout);
    }
    
    memset(buffer, '\0', sizeof(buffer));               // clear buffer
    
    n = recv(sockfd,buffer,255, MSG_WAITALL);           // receive acknowledgment from server
    if (n < 0)
    {
        perror("ERROR reading to socket");
        exit(1);
        
    }
}

/***************************************************
 ** receiveCipher receives the encoded text back
 ** from server.
 ** parameters: c string, socket id
 ** preconditions: empty c string, valid socket id
 ** post condition: received cipher text or error
 ** thrown
 ***************************************************/

void receiveCipher(char originalText[], int sockfd)
{
    if(DEBUG)
    {
        printf("In _DEC RECEIVECIPHER\n");
        fflush(stdout);
    }
    
    char buffer [70000];                            // create buffer
    int n;                                          // var for error checking
    int loop = 1;                                   // loop var
    
    while(loop)
    {
        memset(buffer, '\0', sizeof(buffer));       //clear buffer
        
        n = recv(sockfd,buffer,70000,MSG_WAITALL);  // receive cipher from server
        if (n < 0)                                  // error checking
        {
            perror("otp_dec: ERROR reading from socket in daemon");
            exit(1);
        }
        
        if(strcmp(buffer, "exit")==0)               // if message is exit, we leave loop
            loop = 0;
        
        else                                        // else we store buffer in original message string
        {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(originalText, buffer);
        }
        
        memset(buffer, '\0', sizeof(buffer));       // clear buffer
        
		strcpy(buffer,"ack");                       // send ack back to server
    	n = send(sockfd,buffer,255, 0);
    	if (n < 0)
        {
            perror("otp_dec: ERROR writing to socket in daemon");
            exit(1);
        
        }
    }
}