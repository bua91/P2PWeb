/*
 * FILE NAME: content_tracker.c
 * OWNER: ARUNABHA CHAKRABORTY
 *        AMAN SACHAN
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include "p2psh.h"

int peer_connect(char *ip_address, char *port_number)
{
	int sock_fd;
	struct sockaddr_in server_addr;

	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "p2psh: Error in socket creation!!\n");
		return 0;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	if (inet_pton(AF_INET, ip_address, server_addr.sin_addr) <= 0){
		fprintf(stderr, "p2psh: Error in IP address!!\n");
		return 0;
	}
	if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		fprintf(stderr, "p2psh: Error in socket connect!!\n");
		return 0;
	}
	// write the sending part.
	return 1;
}

/*
 * Show commands.
 * show peer: Displays the peer ip addresses with which the node is
 *            peer with.
 */

int show_peers()
{
	struct peer_socket_info* temp;
	temp = head;
	printf("THE PEERS ARE:\n==============\n\n");
	while (temp != NULL){
		printf("%s\n", inet_ntoa(temp->in_addr));
		temp = temp->next;
	}
	return 1;
}

/*
 * show metadata: Displays the metadata table
 */

int show_metadata()
{
	struct meta_info *temp;
	temp = meta_head;
	printf("METADATA TABLE :\n================\n\n");
	printf("%24s%8s%10s\n", "HASH-VALUE", "FILE-TYPE", "FILE-SIZE");
	while (temp != NULL){
		printf("%24s%8s%10s\n", temp->hash, temp->file_type, temp->file_len);
		temp = temp->next;
	}
	return 1;
}
