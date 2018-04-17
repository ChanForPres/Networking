#include <stdio.h>      
#include <sys/types.h>
#include <string.h> 
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <unistd.h>


int GetLocalhostInformation(char *name, struct in_addr *addr, struct in_addr *mask){
    char Buffer[256];
    struct hostent *LocalHostEntry;
    struct ifaddrs *CurrentIFAddr, *FirstIFAddr;
    int Found = 0;
    
    if(-1 == gethostname(Buffer, 255)){
        return -1;
    }
    LocalHostEntry = gethostbyname(Buffer);
    if(NULL == LocalHostEntry){
        return -1;
    }
    strcpy(name, LocalHostEntry->h_name);
    LocalHostEntry = gethostbyname(name);
    if(NULL == LocalHostEntry){
        return -1;
    }
    bcopy((char *)LocalHostEntry->h_addr, (char *)addr, LocalHostEntry->h_length);
    
    if(0 > getifaddrs(&FirstIFAddr)){
        return -1;
    }
    CurrentIFAddr = FirstIFAddr;
    do{
        if(AF_INET == CurrentIFAddr->ifa_addr->sa_family){
            if(0 == memcmp(&((struct sockaddr_in *)CurrentIFAddr->ifa_addr)->sin_addr, addr, LocalHostEntry->h_length)){
                bcopy((char *)&((struct sockaddr_in *)CurrentIFAddr->ifa_netmask)->sin_addr, (char *)mask, LocalHostEntry->h_length);
                Found = 1;
                break;
            }
        }
        CurrentIFAddr = CurrentIFAddr->ifa_next;
    }while(NULL != CurrentIFAddr);
    freeifaddrs(FirstIFAddr);
    if(!Found){
        return -1;
    }
    return 0;
}


int main (int argc, const char * argv[]) {
    struct in_addr ThisAddress, ThisMask;
    char ThisName[256];
    char AddressBuffer[256];
    
    if(0 == GetLocalhostInformation(ThisName, &ThisAddress, &ThisMask)){
        inet_ntop(AF_INET, &ThisAddress, AddressBuffer, INET_ADDRSTRLEN);
        printf("Hostname = %s\nIP = %s ",ThisName, AddressBuffer);
        inet_ntop(AF_INET, &ThisMask, AddressBuffer, INET_ADDRSTRLEN);
        printf("Mask = %s\n", AddressBuffer);
    }
    else{
        printf("Error calling GetLocalhostInformation\n");
    }
    return 0;
}
