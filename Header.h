/* ******** */
/* INCLUDES */
/* ******** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/* ******* */
/* DEFINES */
/* ******* */

#define YELLOW_TEXT "\033[38;5;11m"
#define BLUE_TEXT "\033[38;5;39m"
#define WHITE_TEXT "\033[38;5;256m"
#define RESET "\e[0m"


/* ******* */
/* STRUCTS */
/* ******* */

typedef struct ChatConnection{

	// Literals
	long int sock;
	long int newSock;
	int retVal;
	int portNumber;

	// Structs
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	struct hostent *host;

	// Other
	socklen_t clientLength;
	pthread_t myThread;

}ChatConnection;


/* ********************** */
/* FUNCTIONS: utilities.c */
/* ********************** */

// Checks for invalid flags.
void checkFlagErrors(int argc, char **argv);

// Checks for parameter errors, and sets/validates the port number. Default port: 7000.
int getPortNumber(int argc, char **argv);

// Prints exit message, closes STDOUT, shuts down both sockets, and exits successfully.
void closeExit0(ChatConnection *thisConnection, bool isClient, char *message);

// Prints error message, closes STDOUT, shuts down both sockets, and exits with error.
void closeExit1(ChatConnection *thisConnection, bool isClient, char *message);


/* ******************** */
/* FUNCTIONS: connect.c */
/* ******************** */

// Attempts to establish a connection between server and client.
void establishConnection(ChatConnection *thisConnection, bool isClient);

// Attempts to etablish client connection to server.
void connectToServer(ChatConnection *thisConnection);

// Sends confirmation message to client upon successful connection to server.
void confirmConnectionToServer(ChatConnection *thisConnection);

// Attempts to establish server connection to client.
void connectToClient(ChatConnection *thisConnection);

// Sends confirmation message to server upon successful connection with client.
void confirmConnectionToClient(ChatConnection *thisConnection);


/* ************************ */
/* FUNCTIONS: sendReceive.c */
/* ************************ */

// Receives messages from server until server sends "Exit".
void * clientReceiveMessage(void *thisConnection);

// Sends messages to server until client sends "Exit".
void clientSendMessage(ChatConnection *thisConnection);

// Receives messages from client until client sends "Exit".
void * serverReceiveMessage(void *thisConnection);

// Sends messages to client until server sends "Exit".
void serverSendMessage(ChatConnection *thisConnection);
