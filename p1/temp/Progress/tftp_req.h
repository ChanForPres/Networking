#ifndef TFTP_REQ

#define TFTP_REQ 
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>


struct IP_header {

    uint16_t source_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;

}; struct IP_header IP_default = {69,NULL,NULL,NULL};





struct WRQ_packet {
    struct IP_header header;
    uint16_t opcode;
    char* filename;
    uint8_t empty;
    char* mode;
    uint8_t empty2;
}; struct WRQ_packet WRQ_default = {IP_default, 2,NULL, 0,"NETASCII" , 0};

struct RRQ_packet {

    struct IP_header header;

    uint16_t opcode;
    char* filename;
    uint8_t empty;
    char* mode;
    uint8_t empty2;

}; struct RRQ_packet RRQ_default = {IP_default, 2,NULL, 0,"NETASCII" , 0};



struct DATA_packet {
struct IP_header header;

uint16_t opcode;
uint16_t block_id;
uint8_t* data;

};

struct ACK_packet {
struct IP_header header;

    uint16_t opcode;
uint16_t block_id;

};

struct ERROR_packet {
struct IP_header header;

    uint16_t opcode;
    uint16_t err_code;
    char* err_msg;
    uint8_t empty;
};








#endif
