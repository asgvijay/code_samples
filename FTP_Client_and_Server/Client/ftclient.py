# ftclient.py
# Vijay Kumar
# Program 2 


from socket import *
import sys # for command line arguments
import os.path


# This block checks all agruments and validates them. 
# If all agruments are correct, the variable cat_command is
# constructed and contains all necessary information for 
# socket setup

if len(sys.argv) <5 or len(sys.argv) >6 :
    sys.exit("This program takes up to six arguments, Program Exec, Server IP (string), Server Port Number (integer), a command (string), a filename (string) and Data Port(integer).")

# set up socket and wait to listen for 1 connection  
if(isinstance(sys.argv[1], str)):
    serverIP = sys.argv[1]
else:
    sys.exit("Your Server Name was an incorrect type: This program takes up to six arguments, Program Exec, Server IP (string), Server Port Number (integer), a command (string), a filename (string) and Data Port(integer).")

serverPort = int(sys.argv[2])

if(serverPort < 1024 or serverPort > 65535):
    sys.exit("Your Server Port Number was not valid: This program takes up to six arguments, Program Exec, Server IP (string), Server Port Number (integer), a command (string), a filename (string) and Data Port(integer).")

command = sys.argv[3]

if len(sys.argv)<6:
    Data_Port = int(sys.argv[4])
    if(Data_Port < 1024 or Data_Port > 65535):
        sys.exit("Your Data Port Number was an incorrect type: This program takes up to six arguments, Program Exec, Server IP (string), Server Port Number (integer), a command (string), a filename (string) and Data Port(integer).")
    cat_command = command + " "
    cat_command = cat_command + str(Data_Port)
    cat_command = cat_command + "\0"
else:
    filename = sys.argv[4]
    Data_Port = int(sys.argv[5])
    if(Data_Port < 1024 or Data_Port > 65535):
        sys.exit("Your Data Port Number was an incorrect type: This program takes up to six arguments, Program Exec, Server IP (string), Server Port Number (integer), a command (string), a filename (string) and Data Port(integer).")
    cat_command = command + " "
    cat_command = cat_command + filename
    cat_command = cat_command + " "
    cat_command = cat_command + str(Data_Port)
    cat_command = cat_command + "\0"
    


# Create Socket for request file from server
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverIP, serverPort))


# Create socket for receiving file from server
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(("", Data_Port))
serverSocket.listen(1)


# Send command to server over Client Socket
clientSocket.send(cat_command)

# Receive response from server
serverReceived = clientSocket.recv(1024) # change 1024 to reflect the size of possible incoming message
# Print Server response. This handles all response from server.
print serverReceived

# If file does not exists.
if(serverReceived == 'This file does not exist'):
    clientSocket.close()
    sys.exit()
    
# If file does not exists.
if(command == '-l'):
    clientSocket.close()
    sys.exit()

# If client sent a -g command, accept a message from server with details about our file request
if(command == '-g'):

    # open up data port socket for receipt of file
    connectionSocket, addr = serverSocket.accept()
    
    # Check if file name exists in our current directory
    # If not, create a file and write incoming message from server to file.
    # File checking line in if statement borrowed from link:
    #http://stackoverflow.com/questions/82831/how-do-i-check-whether-a-file-exists-using-python
    if(not os.path.isfile(filename)):
        newFile = open(filename, "w")
        stream = connectionSocket.recv(536870912)
        newFile.write(stream)
        newFile.close()
        print 'File Transfer Complete.'
    else:
        print 'This file already exists.'

    # close up the socket
    clientSocket.close()

else:
    clientSocket.close()

    
    
    
    
    
    
