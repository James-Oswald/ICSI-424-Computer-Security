#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>

void main()
{
    int sd;
    struct sockaddr_in sin;
    char buffer[1024] = "Lab 08 yay"; 
    sd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(sd < 0) {
        perror("socket() error"); 
        exit(-1);
    }

    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("10.0.2.15");
    sin.sin_port = htons(9090);
    if(sendto(sd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("sendto() error"); exit(-1);
    }
    close(sd);
}
