/* 
 * OWNER: ARUNABHA CHAKRABORTY
 * 	  AMAN SACHAN
 * PURPOSE: IT CONTAINS THE FUNCTION PROTOTYPES AND DATA STRUCTURE NEEDED FOR
 *          p2psh.c
 */
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

/*
 * peer structure definations.
 */
struct peer_socket_info
{
	int client_soc_fd;
	struct in_addr in_addr;
	pthread_t tid;
	struct peer_socket_info* next;
};

/*
 * Metadata structure
 */
struct meta_info
{
	char hash[SHA_DIGEST_LENGTH+1];
	struct in_addr in_addr;
	int file_len;
	char filename[50];
	char file_type[5];
	struct meta_info* next;
};

/*
 * peer list head
 */
struct peer_socket_info* head;

/*
 * metadata list head
 */
struct meta_info* meta_head;

/*
 * function declerations
 */
int peer_connect(char *ip_address, char *port_number);
int server();
int metadata();
int publish_data(char *filename);
int unpublish_data( char *hash);
int show_peers();
int show_published();
int show_metadata();
