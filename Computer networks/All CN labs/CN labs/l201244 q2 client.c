/*
        TCP_Client. This Program will implement the Client Side for TCP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Get Input from the User
        
        printf("Enter Message: ");
        gets(client_message);                                     //One is that gets() will only get character string data. 
                                                       //		will get only one variable at a time.
																//  reads characters from stdin and loads them into str
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Server send this Message: %s\n",server_message);
        
        
       //inverting and displaying code start
         
         	char invert_message[2000];
         
         	char word[255];
	
			int count = 0, Inverted = 0, m_counter = 0, invert_array_counter = 0;
	
			char c = server_message[m_counter++];
	
			while(c != '\0')
			{
	
				if(c == ' ' && count > 0 && Inverted == 1)
				{
					//input word in file
			
					word[count] = ' ';
					++count;
			
					int i = 0;
					
					for(i = 0; i < count; i++)
					{
					
						invert_message[invert_array_counter++] = word[i];
					
					}
			
					Inverted = 0;
		 			
		 			count = -1;
			
		
		
				}
		
				if(c == ' ' && count > 0 && Inverted == 0)
				{
					//input word in file
			
					count--;

					int i = 0;
					
					for(i = count; i >= 0; i--)
					{
					
						invert_message[invert_array_counter++] = word[i];
					
					
					}
					
					invert_message[invert_array_counter++] = ' ';
			
					Inverted = 0;
		 			
		 			count = -1;
			
		
		
				}
		 		
		 		if( c == 'a' || c == 'i' || c == 'o' || c == 'e' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
		 		{
		 			
		 			Inverted = 1;//if vowel then 1
		 			
		 			
		 		}
		 		
		 		if(count > -1)
		 		{
		 		
		 			word[count] = c;
		 		
		 		}
		 		++count;
		 
		 
		 		c = server_message[m_counter++];

			}
	
			if(count > 0 && Inverted == 1)
			{
					//input word in file
			
			
					word[count] = '\0';
					
					++count;

					int i = 0;
					
					for(i = 0; i < count; i++)
					{
					
						invert_message[invert_array_counter++] = word[i];
					
					}
			
			}
	
			if(count > 0 && Inverted == 0)
			{
					//input word in file
			
					--count;
			
			
					int i = 0;
					
					for(i = count; i >= 0; i--)
					{
					
						invert_message[invert_array_counter++] = word[i];
					
					
					}
					
					invert_message[invert_array_counter++] = '\0';
			
		
		
			}
         
         printf("Server's message with invert_of_nonvowels is : %s\n",invert_message);
         
         //inverting and displaying code end
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}