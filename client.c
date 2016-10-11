#include <netinet/in.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <stdio.h>        
#include <stdlib.h>        
#include <string.h>        
/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
*/

#define HELLO_WORLD_SERVER_PORT    6666 
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char **argv)
{
	int64_t counter = 0;

	if (argc < 2)
	{
		printf("Usage: ./%s ServerIPAddress\n",argv[0]);
		exit(1);
	}


	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr)); 
	client_addr.sin_family = AF_INET;    
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);    
/*
	if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
	{
		printf("Client Bind Port Failed!\n"); 
		exit(1);
	}
*/

	printf("begin!\n");

	int64_t times = 10000;
	if (argc > 2) {
	   times = atoi(argv[2]);
        }
	while (counter < times) {

		int client_socket = socket(AF_INET,SOCK_STREAM,0);
		if( client_socket < 0)
		{
			printf("Create Socket Failed!\n");
			exit(1);
		}

		struct sockaddr_in server_addr;
		bzero(&server_addr,sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		if(inet_aton(argv[1],&server_addr.sin_addr) == 0) 
		{
			printf("Server IP Address Error!\n");
			exit(1);
		}
		server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
		socklen_t server_addr_length = sizeof(server_addr);

		if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
		{
			printf("Can Not Connect To %s!\n",argv[1]);
			exit(1);
		}

		//printf("begin!1\n");
		send(client_socket,&counter, sizeof(counter), 0);

		//printf("begin!2\n");
		int length = 0;
		int64_t result = 0;
		while( length = recv(client_socket, &result, sizeof(result), 0))
		{
			//printf("begin!3\n");
			if(length < 0)
			{
				printf("Recieve Data From Server %s Failed!\n", argv[1]);
				break;
			}
		}
		counter = result;

		//printf("begin!4\n");
		if (counter % 1000 == 0) {
			printf("client: %ld round\n", counter);
		}
		//printf("client: %ld round", counter);


		close(client_socket);

	} 
	printf("end!\n");
	return 0;
}
