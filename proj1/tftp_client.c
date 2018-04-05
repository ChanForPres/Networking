 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>


 #define EXIT_FAILURE    1       /* Failing exit status.  */
 #define EXIT_SUCCESS    0       /* Successful exit status.  */



 int main(int argc, char *argv[]) {


if (argc < 3) {
    printf("Too few ARGS!\n");
}

int cli_fd, server_fd, portno;
portno = atoi(argv[2]); //not sure if correct...


// store client info: family, port #, IP
struct sockaddr_in cli_adrs;
memset(&cli_adrs,0,sizeof(cli_adrs));
cli_adrs.sin_family = AF_INET:
// htons function converts btwn host/network byte orders
// if already correct, return
cli_adrs.sin_port = htons(portno);
inet_pton(); // convert IP to human readable


socket(AF_INET ,SOCK_DGRAM, 0 ); //socket, Datagram(udp), default protocol
if (error < 0) {
    perror("error: ");
}

error = connect(cli_fd, ,); //int connect(int sockfd, struct sockaddr *serv_addr, int addrlen); 
if (error < 0) {
    perror("error: ");
}



return 0;
 }
