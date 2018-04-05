#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define EXIT_FAILURE    1       /* Failing exit status.  */
#define EXIT_SUCCESS    0       /* Successful exit status.  */

/*5 types of pckts: Read, Write, Data, Ack, Err */
struct RRQ {
    uint8_t header;
};

struct WRQ {
    uint8_t header;
};

struct DATA {

    uint8_t header;
};

struct ACK {

    uint8_t header;
};

struct ERROR {

    uint8_t header;
};

int main(int argc, char *argv[]) {
    /* Get correct input and route */

    // scanf + strtok
    char buffer[256]; // read up to whitespace 
    // hold address information for server/client
    
    // check argument #: tftpserver [port [rootdir] ]
    // possible args: 1 or 2
    
    // default values for args: 
    char *rootdir = ".";
    int portno = 49999;
    int cli_len, server_fd,cli_fd;
    


    //input: tftpserver [port [rootdir] ]
    if (argc == 1 ) {
        //default ports
    }
    else if (argc ==2 && ( 0 < atoi(argv[1]) < 65,535 ) ) {
        // check if port in range
        
        //assign new port
        // do strcpy for char[]
        // = works for char*
        portno = atoi(argv[1]);
    }

    else if (argc == 3) {
        // check port in range + rootdir exists
        portno = atoi(argv[1]);
        rootdir = argv[2];
    }
    else { 
        // error handle 
         fprintf(stderr,"ERROR, too many args");
         exit(1);
     
    }
    
    struct sockaddr_in serv_addr, cli_addr;
    struct in_addr net_addr; // store
    
    memset(&serv_addr,0,sizeof(serv_addr) );
    memset(&cli_addr,0,sizeof(cli_addr) );
    memset(&net_addr,0,sizeof(net_addr) );
        
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); // assign port from argument, make sure in MSB
    serv_addr.sin_addr = net_addr;
    
    // memset(serv_addr.sin_zero,0,sizeof(long)); // zero out , don't use bzero
    

    // bind socket + connect to client
    
    server_fd = socket(AF_INET, SOCK_DGRAM,0);
    if ( (server_fd)<0 ) {
        printf("Unable to open socket\n"); 
        exit(EXIT_FAILURE);
    
    }
    
    // listen for client access to server
    listen(server_fd,5); //

    // accept the connection 
    cli_fd = accept(server_fd,(struct sockaddr *) &cli_addr ,&cli_len);
    if ( cli_fd < 0) {
        printf("ACCEPT FAILED\n"); //err msg
        exit(EXIT_FAILURE);
    }
    // open
    
    // read/write
    
    while (1) {
        printf("tftp> "); // console input
        scanf("%s",buffer); 

        // choose option to route to 
        // strcmp = 0 then match
        if (!strcmp(buffer,"get") ) {
            printf("get\n");
            exit(1);
        }
        else if (!strcmp (buffer,"push")) {
            printf("push");
            exit(1);
        }
      else if (!strcmp (buffer,"quit")) {
            printf("quit");
            exit(1);
        }
      else if (!strcmp (buffer,"status")) {
            printf("status");
            exit(1);
        }
      else if (!strcmp (buffer,"?" ) ) {
            printf("?\n");
            exit(1); // return restarts loop?
      }

      else {
        // unknown input, cycle
        printf("Ambiguous Input\n");
        exit(1); //repeat loop 
      }
    } 
    return 0;
}
