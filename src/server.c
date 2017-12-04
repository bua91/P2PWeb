/*
 * FILE NAME: server.c
 * OWNER: ARUNABHA CHAKRABORTY
 * 	  AMAN SACHAN
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
#include <pthread.h>
#include "p2psh.h"

/*
 * Peer list addition
 */
int peer_list_add(int con_fd, struct sockaddr_in * addr, pthread_t tid){
	struct peer_socket_info* new_peer = (struct peer_socket_info*) malloc(sizeof(struct peer_socket_info));
	new_peer->client_soc_fd = con_fd;
	new_peer->in_addr = addr->sin_addr;
	new_peer->tid = tid;
	new_peer->next = head;
	head = new_peer;
}

/*
 * Peer handler
 */
void *peer_handler (void *arg){
	//send part
	
	while (1){
		
	}
}

/*
 * server code
 */
int server()
{
        int listen_fd, conn_fd;
	struct sockaddr_in server_addr, cli_addr;
	socklen_t cli_len;
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "p2psh: Error in socket creation!!\n");
		return 0;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(9000);
	
	if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		fprintf(stderr, "p2psh: Error in bind!!\n");
		return 0;
	}
	if (listen(listen_fd, 100)<0){
		fprintf(stderr, "p2psh: Error in listen!!\n");
		return 0;
	}
	while(1){
		cli_len = sizeof(cli_addr);
		if (conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, cli_len)<0){
			fprintf(stderr, "p2psh: Error in accept!!\n");
			return 0;
		}
		//client handler thread
		pthread_create(&tid, &attr, peer_handler, (void *)conn_fd);
		//store this connection fd to peer list
		if (peer_list_add(conn_fd, &cli_addr, tid) < 0){
			fprintf(stderr, "p2psh: Error in peer addition to list!!\n");
			return 0;
		}
	}

}
