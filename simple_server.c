#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "hacking.h"

#define PORT 7890


int main(){
    int sockfd, new_sockfd;

    struct sockaddr_in host_addr, client_addr;
    socklen_t sin_size;
    int yes=1, recv_length=1;
    char buffer[1024];


    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	fatal("Socket creation");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	fatal("During the REUSEADDR parametr setting");

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = 0;
    memset(&(host_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
	fatal("During the socket binding");

    if (listen(sockfd, 5) == -1)
	fatal("During socket listening");

    while(1){
	sin_size = sizeof(struct sockaddr_in);
	new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
	if (new_sockfd == -1)
	    fatal("During the accepting");
	printf("Connection accepted from %s:%d", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	
	send(new_sockfd, "CONNECTION ESTABLISHED", 22, 0);
	recv_length = recv(new_sockfd, &buffer, 1024, 0);
	while (recv_length > 0){
	    printf("RECV: %d bytes", recv_length);
	    dump(buffer, recv_length);
	    recv_length = recv(new_sockfd, &buffer, 1024, 0);
	}
	close(new_sockfd);
    }
    return 0;
}
