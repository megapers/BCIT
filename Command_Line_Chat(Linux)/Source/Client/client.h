#include <stdio.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>


#define SERVER_TCP_PORT         7000    // Default port
#define BUFLEN                  255     // Buffer length


int n, bytes_to_read;
int sd, port;
struct hostent  *hp;
struct sockaddr_in server;
char  *host, *bp, rbuf[BUFLEN], sbuf[BUFLEN], **pptr, *username, *fileName;
char str[16];
fd_set rset, allset;
int sret;
ssize_t input, output;
int file;
int fileCheck;


void clientSelect();
void clientConnect(int, char**);


