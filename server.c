/**
 * @author: Debra-Lee Speight
 */

#include "Header.h"

int main(int argc, char **argv){

	ChatConnection *thisConnection = (ChatConnection*)malloc(sizeof(ChatConnection));

	// Check for errors in flags and parameters (port number).
	checkFlagErrors(argc, argv);
	thisConnection->portNumber = getPortNumber(argc, argv);

	// Attempt to connect with client.
	establishConnection(thisConnection, false);

	// Create a new thread, and start receiving messages from client.
	if((thisConnection->retVal = pthread_create(&thisConnection->myThread, NULL,
											   &serverReceiveMessage, thisConnection)) < 0)
		closeExit1(thisConnection, false, "pthread_create() failed");

	// Can now send messages from server.
	serverSendMessage(thisConnection);

	// Exit program.
	exit(0);
}