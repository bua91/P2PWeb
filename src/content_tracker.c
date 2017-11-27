#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

int peer_connect(char *ip_address, char *port_number)
{
	int sock_fd;
	struct sockaddr_in server_addr;

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("P2PSH: Error in socket creation!!\n");
		return 0;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	if (inet_pton(AF_INET, ip_address, server_addr.sin_addr) <= 0){
		printf("P2PSH: Error in IP address!!\n");
		return 0;
	}
	if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		printf("P2PSH: Error in socket connect!!\n");
		return 0;
	}
	// write the sending part.
}
