/**
 * @author: Debra-Lee Speight
 */

#include "Header.h"

/**
 * Attempts to establish a connection between server and client.
 * @param: thisConnection
 * @param: isClient : Determines whether the calling entity is client.
 */
void establishConnection(ChatConnection *thisConnection, bool isClient){

	// Create TCP socket, and check for failures.
	thisConnection->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(thisConnection->sock < 0){
		perror("socket() failed");
		exit(1);
	}

	// Reset serverAddress memory.
	bzero((char *)&thisConnection->serverAddress, sizeof(thisConnection->serverAddress));

	// Connect ports that apply to both client and server.
	thisConnection->serverAddress.sin_family = AF_INET;
	thisConnection->serverAddress.sin_port = htons(thisConnection->portNumber);

	// Perform client-specific and server-specific connection operations.
	if(isClient) connectToServer(thisConnection);
	else connectToClient(thisConnection);
}

/**
 * Attempts to etablish client connection to server.
 * @param: thisConnection
 */
void connectToServer(ChatConnection *thisConnection){

	// Use localhost as host name for client, and check for failures.
	thisConnection->host = gethostbyname("localhost");
	if(thisConnection->host == NULL)
		closeExit1(thisConnection, true, "gethostbyname() failed");

	// Set server address fields.
	bcopy((char *)thisConnection->host->h_addr_list[0],
		 (char *)&thisConnection->serverAddress.sin_addr.s_addr,
		 thisConnection->host->h_length);

	// Attempt to connect, and check for failures.
	if(connect(thisConnection->sock, (struct sockaddr*)&thisConnection->serverAddress,
			  					 sizeof(thisConnection->serverAddress)) < 0)
		closeExit1(thisConnection, true, "connect() failed");

	// Print confirmation upon successful connection.
	confirmConnectionToServer(thisConnection);
}

/**
 * Sends confirmation message to client upon successful connection to server.
 * @param: thisConnection
 */
void confirmConnectionToServer(ChatConnection *thisConnection){

	// Receives confirmation message from server.
	char confirmChatConnection[100];
	char connected[100] = {"\n\t    .::. Connected with client! .::.\n"};

	// Send confirmation message to server, and check for failures.
	if((thisConnection->retVal = send(thisConnection->sock, connected, 100,0)) < 0)
		closeExit1(thisConnection, true, "send() failed");

	// Receive confirmation message from server, and check for failures.
	if((thisConnection->retVal = recv(thisConnection->sock, confirmChatConnection,
								 sizeof(confirmChatConnection), 0)) < 0)
		closeExit1(thisConnection, true, "recv() failed");

	// Print the confirmation message.
	printf("\n%s\n", confirmChatConnection);
	printf("\t\e[3m        To end chat, type \"\e[0mExit\"\n\n");
}

/**
 * Attempts to establish server connection to client.
 * @param: thisConnection
 */
void connectToClient(ChatConnection *thisConnection){

	thisConnection->serverAddress.sin_addr.s_addr = INADDR_ANY;

	// Attempt to bind, and check for failures.
	if(bind(thisConnection->sock, (struct sockaddr*)&thisConnection->serverAddress,
			sizeof(thisConnection->serverAddress)) < 0){
		perror("bind() failed");
		exit(1);
	}

	// Listen to network for connections with backlog queue of 5.
	listen(thisConnection->sock, 5);

	// Get length of clientAddress structure.
	thisConnection->clientLength = sizeof(thisConnection->clientAddress);

	// Attempt to accept connection, and check for failures.
	if((thisConnection->newSock = accept(thisConnection->sock,
										(struct sockaddr*)&thisConnection->clientAddress,
										&thisConnection->clientLength)) == -1){
		perror("accept() failed");
		exit(1);
	}

	// Print confirmation upon successful connection.
	confirmConnectionToClient(thisConnection);
}

/**
 * Sends confirmation message to server upon successful connection with client.
 * @param: thisConnection
 */
void confirmConnectionToClient(ChatConnection *thisConnection){

	// Receives confirmation message from client.
	char confirmChatConnection[100];
	char connected[100] = {"\n\t    .::. Connected with server! .::.\n"};

	// Send confirmation message to client, and check for failures.
	if((thisConnection->retVal = send(thisConnection->newSock, connected, 100, 0)) < 0)
		closeExit1(thisConnection, false, "send() failed");

	// Receive confirmation message from client, and check for failures.
	if((thisConnection->retVal = recv(thisConnection->newSock, confirmChatConnection,
								 sizeof(confirmChatConnection), 0)) < 0)
		closeExit1(thisConnection, false, "recv() failed");

	// Print the confirmation message.
	printf("\n%s\n", confirmChatConnection);
	printf("\t\e[3m        To end chat, type \"\e[0mExit\"\n\n");
}