//otp_dec_d.c

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
void estConnection(int sockfd, char* message);
void receiveText(char code[], int sockfd);
void decodeText(char plain[], char key[], char decodedText[]);
void sendDecode(char decodedMessage[], int sockfd);

#define DEBUG 0

int main(int argc, char* argv[])
{
    
    if(argc<2)
    {
        perror("otp_enc_d : incorrect number of agruments");
        exit(1);
    }
    
    int clientSock;                                 // create id for client
    
    int sockfd = daemonSetup(atoi(argv[1]));        // set up server socket
	signal(SIGCHLD, SIG_IGN);                       // set up signals
    
    char encodedMessage[70000];                       // create buffers for messages
     memset(encodedMessage, '\0', sizeof(encodedMessage));
    char userKey[70000];
     memset(userKey, '\0', sizeof(userKey));
    char decodedMessage[70000];
     memset(decodedMessage, '\0', sizeof(decodedMessage));
                             
    while(1)
	{
   		
		clientSock = accept(sockfd,NULL, NULL);     // open communcications with client
    	if (clientSock==-1)
        {
            perror("accept call failed");
            exit(1);
        }
        
		if(fork()==0)                               // child process
		{ 			
			estConnection(clientSock,"decAck");     // establish connection with client
            receiveText(encodedMessage, clientSock);// receive encoded text from client
            receiveText(userKey, clientSock);       // recieve user key from client
            decodeText(encodedMessage, userKey, decodedMessage);    // decode text
            sendDecode(decodedMessage, clientSock); // send decoded text to client
			exit(0);
			close(clientSock);
		}
		else
		{ 
			close(clientSock);
		}
	}
    
    close(sockfd);
    return (0);                          

return 0;

}

/***************************************************
 ** deamonSetup creates socket for server to comm
 ** with clients
 ** parameters: int port number
 ** preconditions: valid port number
 ** post condition: socket is set on server or error
 ** thrown
 ***************************************************/

int daemonSetup(int portno)
{
    
    int sockfd;
    struct sockaddr_in server;                          // create server struct
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1)  // open socket on server
    {
        perror("socket");
        exit(1);
    }
  
    bzero((char *) &server, sizeof(server));
    
    server.sin_family = AF_INET;                        // initialize server struct
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &server,sizeof(server))==-1)       // bind socket to server
    {
        perror("ERROR on binding");
        exit(1);
    }
    
	if(listen(sockfd,5)==-1)        // listen for up to 5 clients
    {
        perror("listen call failed");
        exit(1);
        
    }
	
    return sockfd;
    
    
}

/*******************************************************
 ** estConnection establishes connection with client
 ** parameters: socket id, c string
 ** preconditions: valid socket id, initialize c string
 ** post condition: client is properly communicating with
 ** server.
 ******************************************************/
                             
void estConnection(int sockfd, char* message)
{
    
    char buffer[256];           // create buffer
    memset(buffer, '\0', sizeof(buffer));
    
    ssize_t n;
    n = recv(sockfd, buffer, 255, MSG_WAITALL);   // receive message
    
    if(n<0) 
    {
        perror("receive error");
        exit(1);
    }
    
    buffer[strcspn(buffer, "\n")] = 0;
    
    if(strcmp(message, buffer))         // if message didn't compare throw bad auth
    {  
        close(sockfd);
        perror("Bad Auth");
        exit(1);
    
    }

    else                                // if ack was the same,  send message back
    {    
        n=0;
        bzero(buffer, 256);
        strcpy(buffer, message);

        n = send(sockfd, buffer, 255, 0);
        
        if(n<0)
        {
            perror("send error");
            exit(1);
        }
    }
   
}

/***************************************************
 ** receiveText receives the plain text
 ** from client.
 ** parameters: c string, socket id
 ** preconditions: empty c string, valid socket id
 ** post condition: received plain text or error
 ** thrown
 ***************************************************/
                             
void receiveText(char code[], int sockfd)
{
    char buffer [70000];              // create buffer
    
    int n;
    int loop = 1;
    while(loop)
    {
        memset(buffer, '\0', sizeof(buffer));
        n = recv(sockfd,buffer,70000,MSG_WAITALL);  // receive text from client
        
        if (n < 0) 
        {
            perror("otp_dec_d: RECEIVETEXT :ERROR reading from socket in daemon");
            exit(1);
        }
        
        if(strcmp(buffer, "exit")==0)   // if message reads 'exit' then close loop
            loop = 0;
        else
            strcpy(code, buffer);       // else store message in code
        
        memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer,"ack");
        
    	n = send(sockfd,buffer,255, 0);     // send acknowledgement back
    	if (n < 0)
        {
            perror("ERROR writing to socket in daemon");
            exit(1);
        }
    }
                                 
}
                             
/***************************************************
 ** decodeText uses an encoded text and keytext to create
 ** an decoded text.
 ** parameters: c string, c string, c string
 ** preconditions: two initialized strings and one
 ** empty string to receive the encoded text
 ** post condition: decodedText holds the newly
 ** decoded Text
 ***************************************************/
void decodeText(char plain[], char key[], char decodedText[])
{
    int i = 0;      // index
    char p;         // plain text
    char k;         // key text
    char e;         // encoded text
    if(DEBUG)
    {
        printf("otp_dec_d: DECODE TEXT: The encoded text is: %s\n", plain);
        fflush(stdout);
    }
    
    
    while(plain[i]!= '\0')
    {    
        if(plain[i]==32)        // if i is a space make p == 0
            p=0;
        
        else if(plain[i] == '\n') // if i is a \n
            break;
        else
            p = plain[i]-64;    // if i is a capital letter subtract 64
        
        if(key[i]==32)          // if == space, set to 0
            k=0;
        else
            k = key[i]-64;       // else - 64
     
        e = p-k;                //subtract k from p
            
        if(e<0)                 // if e is lower than 0 add 27
            e = e + 27;
        
        if(e == 0)              // put value of e into encodedText string
            decodedText[i]=32;
        else
            decodedText[i]= e + 64;
        
        i++;
    }
    
    
    if(DEBUG)
    {
        printf("otp_dec_d: DECODE TEXT: The decoded text is: %s\n", decodedText);
        fflush(stdout);
    }
}


/***************************************************
 ** senddecode sends string to client
 ** parameters: c string and int
 ** preconditions: initialized c string and valid
 ** socket id
 ** post condition: server has received the message
 ** or error is thrown
 ***************************************************/
void sendDecode(char decodedMessage[], int sockfd)
{
    
    char buffer[70000];           // create buffer
    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, decodedMessage); // store message in buffer
    
    
    
    buffer[strcspn(buffer, "\n")] = 0;
    
    if(DEBUG)
    {
        printf("otp_dec_d: SENDDECODE: The decoded message is: %s\n", buffer);
        fflush(stdout);
    }
    
    int n;
    
    n = send(sockfd,buffer,70000, 0);      // send to client
    
    if (n < 0) 
    {
        perror("ERROR sending decoded string");
        exit(1);
    }
    
    memset(buffer, '\0', sizeof(buffer));
    n = recv(sockfd,buffer,255,MSG_WAITALL);                  // receive acknowledgement
    
    if (n < 0)
    {
        perror("otp_dec_d: ERROR reading from socket");
        exit(1);
    }
    
	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer,"exit");                          // save exit message in buffer
    
    n = send(sockfd,buffer,70000,0);                  // send to client
    
    if(n < 0)
    {
        perror("otp_dec_d: ERROR writing to socket");
        exit(1);
    }
    
	memset(buffer, '\0', sizeof(buffer));
	n = recv(sockfd,buffer,255, MSG_WAITALL);                 // receive acknowledgement
	if (n < 0)
    {
        perror("otp_dec_d: ERROR reading from socket");
        exit(1);
    }
}

                             
                             
                             
                             
                             
                             
                             
                             
                             