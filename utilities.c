/**
 * @author: Debra-Lee Speight
 */

#include "Header.h"

/**
 * Checks for invalid flags.
 * @param: argc : Sent from main().
 * @param: argv : Sent from main().
 */
void checkFlagErrors(int argc, char **argv){

	int checkValue;

	while((checkValue = getopt(argc, argv, "")) != -1){
		switch(checkValue){
			// Check if invalid characters are entered.
			case '?': break;

			// Error-check: Invalid flags.
			default:
				fprintf(stderr, " ");
				exit(1);
		}
	}
}

/**
 * Checks for parameter errors, and sets/validates the port number. Default port: 7000.
 * @param: argc : Sent from main().
 * @param: argv : Sent from main().
 * @return portNumber
 */
int getPortNumber(int argc, char **argv){

	// Default port number.
	int portNumber = 7000;

	// Get user-specified port number if one exists.
	if(argc == 2) portNumber = atoi(argv[1]);

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

	return portNumber;
}

/**
 * Prints exit message, closes STDOUT, shuts down both sockets, and exits successfully.
 * @param: thisConnection
 * @param: isClient : Determines whether the calling entity is client.
 * @param message
 */
void closeExit0(ChatConnection *thisChatConnection, bool isClient, char *message){

	printf("%s", message);
	close(STDOUT_FILENO);

	// Shut down both sockets, and exit successfully.
	if(!isClient) shutdown((long int)thisChatConnection->newSock, 2);
	shutdown((long int)thisChatConnection->sock, 2);
	exit(0);
}

/**
 * Prints error message, closes STDOUT, shuts down both sockets, and exits with error.
 * @param: thisConnection
 * @param: isClient : Determines whether the calling entity is client.
 * @param message
 */
void closeExit1(ChatConnection *thisChatConnection, bool isClient, char *message){

	perror(message);
	close(STDOUT_FILENO);

	// Shut down both sockets, and exit with error.
	if(!isClient) shutdown((long int)thisChatConnection->newSock, 2);
	shutdown((long int)thisChatConnection->sock, 2);
	exit(1);
}