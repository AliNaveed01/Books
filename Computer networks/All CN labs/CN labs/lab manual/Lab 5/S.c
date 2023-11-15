#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>

#define PORTNO 5003

// GLOBAL Variables -- array of strings
char Voters[50][100];        
char hasVoted[50][100];

void *candidateVote(void *clientSocket);
void addcandidate(char *buf);
void writeoutput(char *client, char *vote);
bool hasClientVoted(char *buf);
void addToVotesCasted(char *client);



int main(void)
{
		pthread_t thread_id;
		int noofClients=0;
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
        char server_message[2000], client_message[2000];                 // Sending values from the server and receive from the server we need this

        //Cleaning the client_messages
        for (int i=0;i<50;i++)
		{
			memset(Voters[i], '\0', sizeof(Voters));
			memset(hasVoted[i], '\0', sizeof(hasVoted));
		}
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));     // Set all bits of the padding field//
        
		// reading voters from file.
		FILE *fin = fopen("Voters_List.txt", "r");
			if(fin)
			{
				// read and populate unless EOF
			int i=0;
			while(fgets(Voters[i], sizeof(Voters[i]), fin) != NULL)
			{
				i++;
			}
			else{
				printf("Error in Reading Voters List\n");
				return -1;
			}
			fclose(fin);

        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;               /* Address family = Internet */
        server_addr.sin_port = htons(2000);               // Set port number, using htons function to use proper byte order */
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */
		
		
		
		// BINDING FUNCTION
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
	                            	//bind() passes file descriptor, the address structure,and the length of the address structure
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)                               //This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
		while(noofClients<5)
		{

        	//Accept the incoming Connections
        	client_size = sizeof(client_addr);
       		 client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);          // heree particular client k liye new socket create kr rhaa ha
        
			if (client_sock < 0)
			{
					printf("Accept Failed. Error!!!!!!\n");
					return -1;
			}
			
			printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		       //inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation
        
        	//Receive the message from the client
        
			if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
			{
					printf("Receive Failed. Error!!!!!\n");
					return -1;
			}
        
        	printf("Client Message: %s\n",client_message);
        
        	//Send the message back to client
        
			strcpy(server_message, client_message);
			
			if (send(client_sock, server_message, strlen(client_message),0)<0)
			{
					printf("Send Failed. Error!!!!!\n");
					return -1;
			}
			
			pthread_create(&thread_id, NULL, candidateVote, (void*)client_sock);
			memset(server_message,'\0',sizeof(server_message));
			memset(client_message,'\0',sizeof(client_message));
			noofClients++;
              
		}
        //Closing the Socket
        pthread_exit(NULL);
        close(client_sock);
        close(socket_desc);
        return 0;       
}


void *candidateVote(void *clientSocket) {

	int socket = *(int *)clientSocket;
	int i; int res=-1;
	char client_message[500];
	memset(client_message, '\0', sizeof(client_message));

		// receive client name-CNIC
		recv(socket, client_message, sizeof(client_message), 0);
		printf("CLIENT: %s", client_message);

				for(i=0; Voters[i][0]!='\0'; i++) {
					int len = strlen(buf)-1;
					if(strcmp(Voters[i], buf, len) == 0) 
					{
						res=i;
						break;
					}
				}

			if(res==-1)
			{
				strcpy(client_message, "Sorry. Name-CNIC is invalid. Closing Connection");
				
				if (send(socket, client_message, strlen(client_message), 0) < 0)
				{                        
					printf("Send Failed. Error!!!!!\n");
				}
			}


				// cannot vote more than once for same client
				int res2=-1;
				for(i=0; hasVoted[i][0] != '\0'; i++) {
					int len = strlen(buf)-1;
					if(strncmp(hasVoted[i], buf, len) == 0)
					{
						res=i;
						break;
					}
				}
				if (res2==-1)
				{
					strcpy(client_message, "A client can only vote ONCE.\nClosing Connection\n");
					send(socket, client_message, sizeof(client_message), 0);
					return -1
				}
	
		// remember the voter/client name
		char name[100];
		// ignore the last char in client_message i.e \n
		strcpy(name, client_message, strlen(client_message)-1);

		// send to user the list of candidates
		char candidatesMsg[500];
		strcpy(candidatesMsg, "Welcome. Please specify your Symbol:\n");
		addcandidate(candidatesMsg);
		send(socket, candidatesMsg, strlen(candidatesMsg), 0);

		memset(client_message, '\0', sizeof(client_message));
		recv(socket, client_message, sizeof(client_message), 0);

		addToVotesCasted(name);

		writeoutput(name, client_message);

		strcpy(client_message, "Thank you for casting the vote. Your vote has been recorded.\nClosing Connection.\n");
		send(socket, client_message, sizeof(client_message), 0);

	close(socket);
	free(clientSocket);
	pthread_exit(NULL);
}

void addcandidate(char *buf) {

	FILE *fin = fopen("Candidates_List.txt", "r");

	// read candidates file and append to buf
	char temp[100];
	while(fgets(temp, sizeof(temp), fin) != NULL) {
		strcat(buf, temp);
	}

	fclose(fin);
}

void writeoutput(char *client, char *vote) {

	FILE *fp = fopen("output.txt", "a");
	strcat(client, " ");
	fputs(client, fp);
	fputs(vote, fp);
	printf("%s\n", vote);
	fclose(fp);
}

void addToVotesCasted(char *client) {

	int i;
	for(i=0; hasVoted[i][0] != '\0'; i++) {}
	strcpy(hasVoted[i], client);
}