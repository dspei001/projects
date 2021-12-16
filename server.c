/*
Author: Debra-Lee Speight
Description: Client Server Chat: server.c
	To begin, this program gathers and checks arguments used at the command line.
		OPTIONAL int parameter used for port number.

	NOTE: If port number is not specified, the default port number is 7000.

	Next, the program becomes a server that makes a connection with a client by performing
	the following operations:
		1) Creates a socket
		2) Initializes the socket address structure
		3) Binds the socket to an address
		4) Listens for connections
		5) Accepts a connection from the client
		6) Receives and prints messages from the client
		8) Sends messages to the client
		9) Closes the connection when either client or server sends 'Exit'

	Error-checks include:
		FOR FLAGS:
			Invalid flags

		FOR PARAMETERS:
			Too many parameters
			Invalid range for port number

	--------------
	OUTPUT SAMPLE:
	--------------

		  .::. Connected with client! .::.


	Server message here

	# [Client]: Client message here

	# [Client]: Client message here
	Server message here

		.::. Client now ending connection .::.
				- OR -
		.::. Server now ending connection .::.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define YELLOW_TEXT "\033[38;5;11m"
#define BLUE_TEXT "\033[38;5;39m"
#define WHITE_TEXT "\033[38;5;256m"

// Long int variable, sock, holds return value of socket() which is a file descriptor used for
// referencing the socket. It is global to allow for access from receiveMessage().
long int sock;

// closeExit0() closes STDOUT, shuts down both sockets, and exits with exit(0).
void closeExit0(long int sock, long int newSock){
	long int socket = sock;
	long int newSocket = newSock;

	// Close standard out.
	close(STDOUT_FILENO);

	// Completely shutdown both sockets.
	shutdown(newSocket, 2);
	shutdown(socket, 2);
	exit(0);
}

// closeExit1() closes STDOUT, shuts down both sockets, and exits with exit(1).
void closeExit1(long int sock, long int newSock){
	long int socket = sock;
	long int newSocket = newSock;

	// Close standard out.
	close(STDOUT_FILENO);

	// Completely shutdown both sockets.
	shutdown(newSocket, 2);
	shutdown(socket, 2);
	exit(1);
}

// receiveMessage() receives messages from client until "Exit" message is sent from client.
void * receiveMessage(void *newSocket){
	// Long int variable, newSock, holds socket file descriptor.
	long int newSock = (long int)newSocket;

	// Int variable, retVal, holds recv() return value which is the number of characters received.
	int retVal = 0;

	// Char string, clientMsg, holds message received from the client.
	char clientMsg[2000];

    // Reset clientMsg memory.
    bzero(clientMsg, sizeof(clientMsg));
    
    // Char string, clientMsgWithName, includes client message preceeded by client name.
    char clientMsgWithName[2050];

	// Infinite loop for receiving client messages.
	for(;;){
		// Receive message from client.
		// If recv() fails, print message, shutdown both sockets, and exit.
		if((retVal = recv(newSock, clientMsg, sizeof(clientMsg), 0)) < 0){
			perror("recv() failed");
			closeExit1(sock, newSock);
		}

        // Reset clientMsgWithName memory, add name, concatenate client message.
        bzero(clientMsgWithName, sizeof(clientMsgWithName));
        strcpy(clientMsgWithName, "\n# [Client]: ");
        strcat(clientMsgWithName, clientMsg);
        
		// If client message is 'Exit', print message, shutdown both sockets, and exit.
		if(strcmp(clientMsg, "Exit\n") == 0){
			printf("\n\n\t.::. Client now ending connection .::.\n\n");
			closeExit0(sock, newSock);
		}

		// Else, print client message.
		else if(strcmp(clientMsg, "Exit\n") != 0){
            printf(YELLOW_TEXT);
            fputs(clientMsgWithName, stdout);
		}
        
        printf(WHITE_TEXT);
        printf("\n");
	}

	// Exit thread function.
	pthread_exit(NULL);
}

int main(int argc, char **argv){

	// Begin program with newline.
	printf("\n");

// Variables for getopt portion //

	// Int variables, c for getopt().
	int c;

// Variables for socket/message portion //

	// Structure, sockaddr_in, from netinet/in.h header file.
	// Contains internet address structure.
	struct sockaddr_in serverAddress, clientAddress;

	// socklen_t variable, clientLength, holds size of client address structure.
	socklen_t clientLength;

	// Int variable, portNumber, holds default port number until one is specified by the user.
	int portNumber = 7000;

	// Long int variable, newSock, holds return value of accept() which is a file descriptor used
	// for client communication.
	long int newSock;

	// Int variable, retVal, holds recv() and send() return values which are the number of
	// characters received or sent.
	int retVal = 0;

	// Char string, confirmConnection, receives connection confirmation message.
	char confirmConnection[100];

	// Char string, myMsg, holds server message to send to client.
	char myMsg[2000];
    
// Variables for process/thread portion //

	// pthread_t variable, myThread, holds thread ID.
	pthread_t myThread;


//////// ERROR-CHECKS FOR FLAGS ////////


	// While-loop checks flags used.
	while((c = getopt(argc, argv, "")) != -1){
		switch(c){
			// Check if invalid characters are entered.
			case '?':
				break;

			// Error-check: Invalid flags.
			default:
				fprintf(stderr, " ");
				exit(1);
		}
	}


//////// ERROR-CHECKS FOR PARAMETERS ////////


	// Error-check: Too many parameters.
	if(argc > 2){
		printf("Error: Too many parameters.\n");
		exit(1);
	}

	// Get user port number if one is specified.
	if(argc == 2){
		portNumber = atoi(argv[1]);
	}

	// Error-check: Invalid range for port number.
	if(portNumber < 7000 || portNumber > 7100){
		printf("Error: Invalid range for port number.\n");
		exit(1);
	}


//////// END ALL ERROR-CHECKS ////////


//////// BEGIN SERVER-SIDE OPERATIONS ////////


	// Function call to create TCP socket.
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// If socket() fails, print message and exit.
	if(sock < 0){
		perror("socket() failed");
		exit(1);
	}

	// Reset serverAddress memory.
	bzero((char *)&serverAddress, sizeof(serverAddress));

	// Initialize the socketAddress structure, and connect to port.
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNumber);

	// Call bind. If bind() fails, print message and exit.
	if(bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
		perror("bind() failed");
		exit(1);
	}

	// Listen to network for connections with backlog queue of 5.
	listen(sock, 5);

	// Get length of clientAddress structure.
	clientLength = sizeof(clientAddress);

	// Accept a connection.
	// If accept() fails, print message and exit.
	if((newSock = accept(sock, (struct sockaddr *)&clientAddress, &clientLength)) == -1){
		perror("accept() failed");
		exit(1);
	}

	// Sned confirmation message to client that connection has been established.
	// If send() fails, print message, close both sockets, and exit.
	if((retVal = send(newSock, "\t    .::. Connected with server! .::.\n", 100,0)) < 0){
		perror("send() failed");
		closeExit1(sock, newSock);
	}
    
	// Receive confirmation message from client that connection has been established.
	// If recv() fails, print message, close both sockets, and exit.
	if((retVal = recv(newSock, confirmConnection, sizeof(confirmConnection), 0)) < 0){
		perror("recv() failed");
		closeExit1(sock, newSock);
	}

	// Print connection confirmation message.
	printf("\n%s\n", confirmConnection);
    printf("\t\e[3m        To end chat, enter: \e[0mExit\n\n");
    
	// Create new thread for receiving messages from client.
	if((retVal = pthread_create(&myThread, NULL, receiveMessage, (void *)newSock)) < 0){
		perror("pthread_create() failed");
		closeExit1(sock, newSock);
	}

	// Reset myMsg memory.
	bzero(myMsg, sizeof(myMsg));

	// While loop continues to send messages from server until server sends "Exit" message.
	while(fgets(myMsg, sizeof(myMsg), stdin) != NULL){
        printf("\n");
        
		// Send server message.
		// If send() fails, print message, close both sockets, and exit.
		if((retVal = send(newSock, myMsg, sizeof(myMsg), 0)) < 0){
			perror("send() failed");
			closeExit1(sock, newSock);
		}
        
        // If server message is 'Exit', print message, close both sockets, and exit.
        if(strcmp(myMsg, "Exit\n") == 0){
			printf("\n\n\t.::. Now ending connection with client .::.\n\n");
			closeExit0(sock, newSock);
		}
	}

	// Exit program.
	exit(0);
}
