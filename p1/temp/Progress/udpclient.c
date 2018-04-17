 #include "tftp_req.h"
#include <mach/error.h>
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

int  cnnct_sock(char* buff ) {


}
int writeFile() {
// send wrq to port 69


// receive ack
// begin send
// send fail

}


int readFile() {


}

int main(int argc, char *argv[]){
    int SocketFileDescriptor, PortNumber, Result;
    socklen_t ServerLength;
    struct sockaddr_in ServerAddress;
    struct hostent *Server;
    char Buffer[BUFFER_SIZE];
    
    if(3 > argc){
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    PortNumber = atoi(argv[2]);
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
    // Convert/resolve host name 
    Server = gethostbyname(argv[1]);
    if(NULL == Server){
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    // Setup ServerAddress data structure
    bzero((char *) &ServerAddress, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    bcopy((char *)Server->h_addr, (char *)&ServerAddress.sin_addr.s_addr, Server->h_length);
    // why use htons here? -> make sure sending is in right
    // format!
    ServerAddress.sin_port = htons(PortNumber); 
    
    printf("Please enter the message: ");
    bzero(Buffer, BUFFER_SIZE);
    fgets(Buffer, BUFFER_SIZE-1, stdin);
    // Send data to server
    Result = sendto(SocketFileDescriptor, Buffer, strlen(Buffer), 0, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
    if(0 > Result){ 
        error("ERROR sending to server");
    }
    ServerLength = sizeof(ServerAddress);
    // Receive message from server
    Result = recvfrom(SocketFileDescriptor, Buffer, BUFFER_SIZE, 0, (struct sockaddr *)&ServerAddress, &ServerLength);
    if(0 > Result){
        error("ERROR receive from server");
    }
    Buffer[Result] = '\0';
    printf("%s\n",Buffer);    
    close(SocketFileDescriptor);
    return 0;
}
