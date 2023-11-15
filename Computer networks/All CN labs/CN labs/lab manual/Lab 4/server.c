/*
        UDP_Server. This Program will will create the Server side for UDP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //// Needed for socket creating and binding
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <stdbool.h>

#define PORTNO 3000


char DB[100][8] = {'\0'}; //2nd index is 8 because XX-XXXX-XX is 8 characters long


bool checkIn(char *buf) {

    // take only the first 8 chars in buf
    char temp[8];
    strncpy(temp, buf, 7);
    temp[7] = '\0';  //placing null in the end

    // check if temp exist in db
    int i;
    for(i=0; DB[i][0]!='\0'; i++) {
        if(strcmp(DB[i], temp) == 0) {
            return false;  //if it already exists in the db, we will return false
        }
    }

    // coming to this point means temp doesn't exist in DB
    // add and return true
    strcpy(DB[i], temp);
    return true;
}

void removeFromDB(int i) {

    // remove i'th row from DB
    // shift rows below DB 1 step above
    for(; DB[i][0]!='\0'; i++) {
        strcpy(DB[i], DB[i+1]);
    }
}

bool checkOut(char *buf) {

    // take only the first 8 chars in buf
    char temp[8];
    strncpy(temp, buf,7);
    temp[7] = '\0';

    // check if temp exist in db
    int i;
    for(i=0; DB[i][0]!='\0'; i++) {
        if(strcmp(DB[i], temp) == 0) {
            // temp found. remove it from db and return true
            removeFromDB(i);
            return true;
        }
    }
    // coming to this point means temp doesn't exist in DB
    return false;
}



int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr, client_addr; 
        int client_struct_length = sizeof(client_addr);
        
        //Creating UDP Socket
        socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        printf("Socket Created\n");
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORTNO);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // bind your socket to localhost only, if you want connect any particular ip you should mention it in INET_ADDR.
        
        //Binding IP and Port to socket
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        printf("Bind Done\n");
        printf("Listening for Messages...\n\n");
        
        while(1) {

            //delcaring and cleaning the Buffers
            char clientmessage[2000];
            char servermessage[2000];
            memset(clientmessage,'\0',sizeof(clientmessage));
            memset(servermessage, '\0', sizeof(servermessage));

            //Receive message from the client
            if (recvfrom(socket_desc, clientmessage, sizeof(clientmessage), 0, (struct sockaddr*)&client_addr, (socklen_t*)&client_struct_length) < 0)
            {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
            }
            printf("Received Message from IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
            printf("Client Message: %s\n",clientmessage);

          

            // determine if it is check-in/out
            if(clientmessage[8]=='C' && clientmessage[9]=='I') {
                
                //check-in
                if(checkIn(clientmessage) == true) //means that the student doesn't exist before
                 {
                    // checkIn successful, welcome the client
                    strcpy(servermessage, "Welcome Student ");
                    strncat(servermessage, clientmessage, 7);
                    sendto(socket_desc, servermessage, sizeof(servermessage), 0, (struct sockaddr*)&client_addr, client_struct_length);
                }
                else   // the client must already be here
                {
                   
                    strcpy(servermessage, "You are already here");
                    sendto(socket_desc, servermessage, sizeof(servermessage), 0, (struct sockaddr*)&client_addr, client_struct_length);
                }
            }
            else if(clientmessage[8]=='C' && clientmessage[9]=='O') {

                // check-out
                if(checkOut(clientmessage) == true) {
                    // checkOut successful, say bye to student/client
                    strcpy(servermessage, "Good Bye. Have a nice day!");
                    sendto(socket_desc, servermessage, sizeof(servermessage), 0, (struct sockaddr*)&client_addr, client_struct_length);
                }
                else {
                    // the client did not mark check in
                    strcpy(servermessage, "You didn’t check in today. Contact System Administrator.");
                    sendto(socket_desc, servermessage, sizeof(servermessage), 0, (struct sockaddr*)&client_addr, client_struct_length);                    
                }
            }
            else {
                //invalid format
                strcpy(servermessage, "Invalid Format");
                sendto(socket_desc, servermessage, sizeof(servermessage), 0, (struct sockaddr*)&client_addr, client_struct_length);                  
            }
            
        }   
        //Closing the Socket        
        close(socket_desc);
        return 0;       
}


