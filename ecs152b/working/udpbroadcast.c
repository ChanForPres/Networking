#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFFER_SIZE     256

void error(const char *message){
    perror(message);
    exit(0);
}

int SocketFileDescriptor;

void SignalHandler(int param){
    close(SocketFileDescriptor);
    exit(0);
}

int main(int argc, char *argv[]){
    int SocketFileDescriptor, PortNumber, Result, BroadcastEnable;
    socklen_t ServerLength;
    struct sockaddr_in ServerAddress;
    char Buffer[BUFFER_SIZE];
    
    if(2 > argc){
        fprintf(stderr,"usage %s port\n", argv[0]);
        exit(0);
    }
    PortNumber = atoi(argv[1]);
    if((1 > PortNumber)||(65535 < PortNumber)){
        fprintf(stderr,"Port %d is an invalid port number\n",PortNumber);
        exit(0);
    }
    // Create UDP/IP socket
    printf("Creating socket\n");
    SocketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(0 > SocketFileDescriptor){
        error("ERROR opening socket");
    }
    
    // Set UDP socket to enable broadcast
    BroadcastEnable = 1;
    Result = setsockopt(SocketFileDescriptor, SOL_SOCKET, SO_BROADCAST, &BroadcastEnable, sizeof(BroadcastEnable));
    if(0 > Result){
        close(SocketFileDescriptor);
        error("ERROR setting socket option");
    }
    
    signal(SIGTERM, SignalHandler);
    signal(SIGINT, SignalHandler);
    signal(SIGUSR1, SignalHandler);
    
    // Setup ServerAddress data structure
    bzero((char *) &ServerAddress, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    ServerAddress.sin_port = htons(PortNumber);
    
    while(1){
        printf("Please enter the message: ");
        bzero(Buffer, BUFFER_SIZE);
        fgets(Buffer, BUFFER_SIZE-1, stdin);
        // Send data to server
        Result = sendto(SocketFileDescriptor, Buffer, strlen(Buffer), 0, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
        if(0 > Result){ 
            error("ERROR sending to server");
        }
        printf("Message sent\n");
    }
    close(SocketFileDescriptor);
    return 0;
}
