Vijay Kumar
Program 2

README


Server:

To compile use:

gcc -o ftserver ftserver.c

To run use:

ftserver <your port number>

Client:

To run/compile us:

python ftclient.py <server host name> <server port number> <command> <filename> <data port number>

Available Commands: -l, -g

-l will print of available files in server directory
-g will attempt to send file requested in <filename> command.
