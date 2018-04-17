#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>


#define BUFFER_SIZE     256

// edit later 
struct Headers {
     uint8_t local_medium;
     uint8_t internet;
     uint8_t datagram;
     uint8_t tftp_opcode;
 }const Headers_default = {0,0,0,0} ;


/*5 types of TFTP pckts: Read, Write, Data, Ack, Err */
 struct RRQ_s {
          uint16_t opcode;
          char* filename;
          uint8_t empty;
          char* mode;
          uint8_t empty2;
 } const RRQ_default = {1,NULL,0,"netascii",0};
 typedef struct RRQ_s RRQ; 


 struct WRQ {
          uint16_t opcode;
          char* filename;
          uint8_t empty;
          char* mode;
          uint8_t empty2;
 } const WRQ_default = {2,NULL,0,"netascii",0};
 
 struct DATA {
           uint16_t opcode;
           uint16_t block_num; // begin with 1 , +1 every block
           uint8_t *data;
 } const DATA_default = {3,-1,NULL};
 
 struct ACK {
           uint16_t opcode;
           uint16_t block_num;

           }const ACK_default = {4,-1};
 
 struct ERROR {
     uint16_t opcode;
     uint16_t Error_code;
     char* err_msg;
          uint8_t empty;
           }const ERROR_default = {5,-1,NULL,0};
 

void error(const char *message){
    perror(message);
    exit(0);
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
    ServerAddress.sin_port = htons(PortNumber);
    
    printf("Please enter the message: ");
    bzero(Buffer, BUFFER_SIZE);
    fgets(Buffer, BUFFER_SIZE-1, stdin);
    // Send data to server
    

    RRQ rrq_packet = {};
    // begin read request  
    Result = sendto(SocketFileDescriptor, (void*)&rrq_packet,sizeof(rrq_packet), 0, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
    // Result = sendto(SocketFileDescriptor, Buffer, strlen(Buffer), 0, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
    
    if(0 > Result){ 
        error("ERROR sending to server");
    }
    ServerLength = sizeof(ServerAddress);
    // Receive ack from tftp server    
    Result = recvfrom(SocketFileDescriptor, Buffer, BUFFER_SIZE, 0, (struct sockaddr *)&ServerAddress, &ServerLength);
    if(0 > Result){
        error("ERROR receive from server");
    }
    Buffer[Result] = '\0';
    printf("%s\n",Buffer);    
    close(SocketFileDescriptor);
    return 0;
}
