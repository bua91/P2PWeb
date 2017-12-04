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
#include "stdlib.h"
#include <netdb.h>
#include <unistd.h>
#include "p2psh.h"

int peer_connect(char *ip_address, char * port_number)
{
	int sock_fd;
	struct sockaddr_in server_addr;
	struct meta_info *temp = meta_head;
	char temp_hash[SHA_DIGEST_LENGTH+1];
	char temp_ip[INET_ADDRSTRLEN];
	char temp_filelen[15];
	char temp_filetype[5];
	char send_buffer[1024];
	char recv_buffer[1024];
	
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "p2psh: Error in socket creation!!\n");
		return 0;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0){
		fprintf(stderr, "p2psh: Error in IP address!!\n");
		return 0;
	}
	if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		fprintf(stderr, "p2psh: Error in socket connect!!\n");
		return 0;
	}
	// write the sending part.
	while (temp != NULL){
		strcpy(temp_hash, temp->hash);
		strcpy(temp_filetype, temp->file_type);
		sprintf(temp_filelen, "%d", temp->file_len);
		//itoa(temp->file_len, temp_filelen, 10);
		inet_ntop(AF_INET, &temp->in_addr, temp_ip, INET_ADDRSTRLEN);
		strcat(send_buffer,temp_hash);
		strcat(send_buffer,"*");
		strcat(send_buffer,temp_filelen);
		strcat(send_buffer,"*");
		strcat(send_buffer,temp_filetype);
		strcat(send_buffer,"*");
		strcat(send_buffer,temp_ip);
		strcat(send_buffer,"*");
		send (sock_fd, send_buffer, strlen(send_buffer), 0);
		bzero(temp_hash, SHA_DIGEST_LENGTH);
		bzero(temp_filelen, 15);
		bzero(temp_filetype,5);
		bzero(temp_ip, INET_ADDRSTRLEN);
		temp = temp->next;
	}
	
	/* Recv data from server and add in the metadata list*/
	

	return 1;
}

int publish_data(char *filename)
{
	return 1;
}

int unpublish_data(char *hash)
{
	return 1;
}
/*
int publish_data(char *filename)
{
	struct meta_info *temp;
	temp = meta_head;
	while(temp != NULL){
		if (strcmp(temp->filename, filename) == 0){
			while 	
*/

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

/*
 * show published: Displayes the published table
 */

int show_published()
{
	return 1;
}
