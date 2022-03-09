/**
 * @author: Debra-Lee Speight
 */

#include "Header.h"

/**
 * Receives messages from server until server sends "Exit".
 * @param: connection
 */
void * clientReceiveMessage(void *connection){

	// Cast from (void *).
	ChatConnection *thisConnection;
	thisConnection = (ChatConnection*)connection;

    // Will include server message preceeded by server name.
    char serverMsgWithName[2050];

	// Holds message received from server.
	char serverMsg[2000];

	// Infinite loop for receiving server messages. Checks for recv() failures first.
	for(;;){
		if((thisConnection->retVal = recv(thisConnection->sock, serverMsg,
										 sizeof(serverMsg), 0)) < 0)
			closeExit1(thisConnection, true, "recv() failed");

        // Prepend server name to server message.
        bzero(serverMsgWithName, sizeof(serverMsgWithName));
        strcpy(serverMsgWithName, "\n# [Server]: ");
        strcat(serverMsgWithName, serverMsg);

		// Exit if server sends "Exit".
		if(strcmp(serverMsg, "Exit\n") == 0)
			closeExit0(thisConnection, true, 
					  "\n\n\t.::. Server now ending connection .::.\n\n");

		// Else, print server message with text color and reset back to white.
		else if(strcmp(serverMsg, "Exit\n") != 0){
            printf(BLUE_TEXT);
			fputs(serverMsgWithName, stdout);			
		}
        printf(WHITE_TEXT);
		fflush(stdout);
	}

	pthread_exit(NULL);
}

/**
 * Sends messages to server until client sends "Exit".
 * @param: thisConnection
 */
void clientSendMessage(ChatConnection *thisConnection){

	// Holds client message to send to server.
	char myMsg[2000];

	// Reset myMsg memory.
	// bzero(myMsg, sizeof(myMsg));

	// Send messages from client until client enters "Exit".
	while(fgets(myMsg, sizeof(myMsg), stdin) != NULL){

		// Send client message, and check for failures.
		if((thisConnection->retVal = send(thisConnection->sock, myMsg,
										 sizeof(myMsg), 0)) < 0)
			closeExit1(thisConnection, true, "send() failed");

		// Check for "Exit".
		if(strcmp(myMsg, "Exit\n") == 0)
			closeExit0(thisConnection, true,
					  "\n\n\t.::. Now ending connection with server .::.\n\n");
	}
}

/**
 * Receives messages from client until client sends "Exit".
 * @param: connection
 */
void * serverReceiveMessage(void *connection){

	// Cast from (void *).
	ChatConnection *thisConnection;
	thisConnection = (ChatConnection*)connection;

    // Will include server message preceeded by client name.
    char clientMsgWithName[2050];

	// Holds message received from client.
	char clientMsg[2000];

	// Infinite loop for receiving client messages. Checks for recv() failures first.
	for(;;){
		if((thisConnection->retVal = recv(thisConnection->newSock, clientMsg,
										 sizeof(clientMsg), 0)) < 0)
			closeExit1(thisConnection, false, "recv() failed");

       // Prepend client name to client message.
        bzero(clientMsgWithName, sizeof(clientMsgWithName));
        strcpy(clientMsgWithName, "\n# [Client]: ");
        strcat(clientMsgWithName, clientMsg);

		// Exit if client sends "Exit".
		if(strcmp(clientMsg, "Exit\n") == 0)
			closeExit0(thisConnection, false,
					  "\n\n\t.::. Client now ending connection .::.\n\n");

		// Else, print client message with text color and reset back to white.
		else if(strcmp(clientMsg, "Exit\n") != 0){
            printf(YELLOW_TEXT);
            fputs(clientMsgWithName, stdout);
		}
        printf(WHITE_TEXT);
		fflush(stdout);
	}

	pthread_exit(NULL);
}


/**
 * Sends messages to client until server sends "Exit".
 * @param: thisConnection
 */
void serverSendMessage(ChatConnection *thisConnection){

	// Holds server message to send to client.
	char myMsg[2000];

	// Reset myMsg memory.
	// bzero(myMsg, sizeof(myMsg));

	// Send messages from server until server enters "Exit".
	while(fgets(myMsg, sizeof(myMsg), stdin) != NULL){

		// Send server message, and check for failures.
		if((thisConnection->retVal = send(thisConnection->newSock, myMsg,
										 sizeof(myMsg), 0)) < 0)
			closeExit1(thisConnection, false, "send() failed");

		// Check for "Exit".
	    if(strcmp(myMsg, "Exit\n") == 0)
			closeExit0(thisConnection, false,
					  "\n\n\t.::. Now ending connection with client .::.\n\n");
	}
}