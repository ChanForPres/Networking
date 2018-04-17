/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include "tftp_req.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE     256

void error(const char *message){
    perror(message);
    exit(1);
}
int cnnct_sock(char* buff ) {
// receive wrqrrq

    
    //sizeof(buff)

// begin write

// send ack



// begin read
return 0; // succeed
}

int readFile() {
    // while (!SocketFileDescriptor)
    // send data
    // {} 
    // receive ack
    
    
return 0;

}



int writeFile () {

return 0;
}

int main(int argc, char *argv[]){
    int SocketFileDescriptor, NewSocketFileDescriptor, PortNumber;
    socklen_t ClientLength;
    char Buffer[BUFFER_SIZE];
    struct sockaddr_in ServerAddress, ClientAddress;
    int Result;
    
    if(2 > argc){
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    PortNumber = atoi(argv[1]);
    if((1 > PortNumber)||(65535 < PortNumber)){
        fprintf(stderr,"Port %d is an invalid port number\n",PortNumber);
        exit(0);
    }
    // Create UDP/IP socket
    SocketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(0 > SocketFileDescriptor){
        error("ERROR opening socket");
    }
    // Setup ServerAddress data structure
    bzero((char *) &ServerAddress, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    ServerAddress.sin_port = htons(PortNumber);
    // Binding socket to port
    if(0 > bind(SocketFileDescriptor, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress))){ 
        error("ERROR on binding");
        perror("bind");

    }
    ClientLength = sizeof(ClientAddress);
    bzero(Buffer, BUFFER_SIZE);
    // Receive message from client
    Result = recvfrom(SocketFileDescriptor, Buffer, BUFFER_SIZE, 0, (struct sockaddr *)&ClientAddress, &ClientLength);
    if(0 > Result){
        error("ERROR receive from client");
    }
    printf("Here is the message: %s\n", Buffer);
    // Send message to client
    Result = sendto(SocketFileDescriptor, "I got your message", 18, 0, (struct sockaddr *)&ClientAddress, ClientLength);
    if(0 > Result){
        error("ERROR sending to client");
    }
    close(SocketFileDescriptor);
    return 0; 
}
