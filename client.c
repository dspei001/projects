/**
 * @author: Debra-Lee Speight
 */

#include "Header.h"

int main(int argc, char **argv){

	ChatConnection *thisConnection = (ChatConnection*)malloc(sizeof(ChatConnection));

	// Check for errors in flags and parameters (port number).
	checkFlagErrors(argc, argv);
	thisConnection->portNumber = getPortNumber(argc, argv);

	// Attempt to connect to server.
	establishConnection(thisConnection, true);

	// Create a new thread, and start receiving messages from server.
	if((thisConnection->retVal = pthread_create(&thisConnection->myThread, NULL,
											   &clientReceiveMessage, thisConnection)) < 0)
		closeExit1(thisConnection, true, "pthread_create() failed");

	// Can now send messages from client.
	clientSendMessage(thisConnection);

	// Exit program.
	exit(0);
}