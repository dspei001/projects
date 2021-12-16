/*
Author: Debra-Lee Speight
Description: Client Server Chat: client.c
	To begin, this program gathers and checks flags used at the command line.
		OPTIONAL int parameter used for port number.

	NOTE: If port number is not specified, the default port number is 7000.

	Next, the program becomes a client that makes a connection with a server by performing
	the following operations:
		1) Creates a socket
		2) Initializes the socket address structure relative to the server
		3) Connects the socket to the server address
		4) Sends the messages to the server
		5) Receives and prints messages from the server
		6) Closes the connection when server or client sends 'Exit'

	Error-checks include:
		FOR FLAGS:
			Invalid flags

		FOR FLAG ARGUMENTS AND PARAMETERS:
			Too many parameters
			Invalid range for port number

	--------------
	OUTPUT SAMPLE:
	--------------

		  .::. Connected with server! .::.


	Client message here

	# [Server]: Server message here

	# [Server]: Server message here
	Client message here


		.::. Server now ending connection .::.
				- OR -
		.::. Now ending connection with server .::.
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
#include <netdb.h>

#define YELLOW_TEXT "\033[38;5;11m"
#define BLUE_TEXT "\033[38;5;39m"
#define WHITE_TEXT "\033[38;5;256m"

// closeExit0() closes STDOUT, shuts down socket, and exits with exit(0).
void closeExit0(long int sock){
	long int socket = sock;

	close(STDOUT_FILENO);

	shutdown(socket, 2);
	exit(0);
}

// closeExit1() closes STDOUT, shuts down socket, and exits with exit(1).
void closeExit1(long int sock){
	long int socket = sock;

	close(STDOUT_FILENO);

	shutdown(socket, 2);
	exit(1);
}

// receiveMessage() receives messages from serevr until "Exit" message is sent from serevr.
void * receiveMessage(void *socket){
	// Long int variable, sock, holds socket file descriptor.
	long int sock = (long int)socket;

	// Int variable, retVal, holds recv() return value which is the number of characters received.
	int retVal = 0;

	// Char string, serverMsg, holds message received from server.
	char serverMsg[2000];
    
    // Reset serverMsg memory.
    bzero(serverMsg, sizeof(serverMsg));
    
    // Char string, serverMsgWithName, includes server message preceeded by server name.
    char serverMsgWithName[2050];

	// Infinite loop for receiving server messages.
	for(;;){
		// Receive message from server.
		// If recv() fails, print message, close socket, and exit.
		if((retVal = recv(sock, serverMsg, sizeof(serverMsg), 0)) < 0){
			perror("recv() failed");
			closeExit1(sock);
        }

        // Reset serverMsgWithName memory, add name, concatenate server message.
        bzero(serverMsgWithName, sizeof(serverMsgWithName));
        strcpy(serverMsgWithName, "\n# [Server]: ");
        strcat(serverMsgWithName, serverMsg);
        
		// If server message is 'Exit', print message, close socket, and exit.
		if(strcmp(serverMsg, "Exit\n") == 0){
			printf("\n\n\t.::. Server now ending connection .::.\n\n");
			closeExit0(sock);
		}

		// Else, print server message with text color.
		else if(strcmp(serverMsg, "Exit\n") != 0){
            printf(BLUE_TEXT);
			fputs(serverMsgWithName, stdout);
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
	struct sockaddr_in serverAddress;

	// Structure, hostent, from netdb.h header file.
	struct hostent *host;

	// Int variable, portNumber, holds default port number until one is specified by the user.
	int portNumber = 7000;

	// Int variable, sock, holds return value of socket() which is a file descriptor used for
	// referencing the socket.
	long int sock;

	// Int variable, retVal, holds send() and recv() return values which are the number of
	// characters sent or received.
	int retVal = 0;

	// Char string, confirmConnection, receives connection confirmation message.
	char confirmConnection[100];

	// Char string, myMsg, holds client message to send to server.
	char myMsg[2000];

// Variables for thread portion //

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


//////// ERROR-CHECKS FOR FLAG ARGUMENTS & PARAMETERS////////


	// Get user-specified port number if one exists.
	if(argc == 2){
		portNumber = atoi(argv[1]);
	}

	// Error-check: Too many parameters.
	if(argc > 2){
		printf("Error: Too many parameters.\n");
		exit(1);
	}

	// Error-check: Invalid range for port number.
	if(portNumber < 7000 || portNumber > 7100){
		printf("Error: Invalid range for port number.\n");
		exit(1);
	}


//////// END ALL ERROR-CHECKS ////////


//////// BEGIN CLIENT-SIDE OPERATIONS ////////


	// Function call to create TCP/IP socket.
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// If socket() fails, print message and exit.
	if(sock < 0){
		perror("socket() failed");
		exit(1);
	}

	// Reset serverAddress memory.
	bzero((char *)&serverAddress, sizeof(serverAddress));

	// Initialize the socket address structure.
	serverAddress.sin_family = AF_INET;

	// Use localhost as host name for client.
	host = gethostbyname("localhost");

	// If gethostbyname() fails, print message, close socket, and exit.
	if(host == NULL){
		perror("gethostbyname() failed");
		closeExit1(sock);
	}

	// Set server address fields.
	bcopy((char *)host->h_addr_list[0], (char *)&serverAddress.sin_addr.s_addr, host->h_length);

	// Connect to port.
	serverAddress.sin_port = htons(portNumber);

	// If connect() fails, print message, close socket, and exit.
	if(connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
		perror("connect() failed");
		closeExit1(sock);
	}

	// Send confirmation message to server that connection has been established.
	// If send() fails, print message, close socket, and exit.
	if((retVal = send(sock, "\t    .::. Connected with client! .::.\n", 100, 0)) < 0){
		perror("send() failed");
		closeExit1(sock);
	}

	// Receive confirmation message from server that connection has been established.
	// If recv() fails, print message, close socket, and exit.
	if((retVal = recv(sock, confirmConnection, sizeof(confirmConnection), 0)) < 0){
		perror("recv() failed");
		closeExit1(sock);
	}

	// Print connection confirmation message.
	printf("\n%s\n", confirmConnection);
    printf("\t\e[3m        To end chat, enter: \e[0mExit\n\n");
    
	// Create new thread for receiving messages from the server.
	if((retVal = pthread_create(&myThread, NULL, receiveMessage, (void *) sock)) < 0){
		perror("pthread_create() failed");
		closeExit1(sock);
	}

	// Reset myMsg memory.
	bzero(myMsg, sizeof(myMsg));

	// While loop continues to send messages from client until client sends "Exit" message.
	while(fgets(myMsg, sizeof(myMsg), stdin) != NULL){
        printf("\n");
        
		// Send client message.
		// If send() fails, print message, close socket, and exit.
		if((retVal = send(sock, myMsg, sizeof(myMsg), 0)) < 0){
			perror("send() failed");
			closeExit1(sock);
		}
        
		// If client message is 'Exit', print message, close socket, and exit.
		if(strcmp(myMsg, "Exit\n") == 0){
			printf("\n\n\t.::. Now ending connection with server .::.\n\n");
			closeExit0(sock);
		}
	}

	// Exit program.
	exit(0);
}
