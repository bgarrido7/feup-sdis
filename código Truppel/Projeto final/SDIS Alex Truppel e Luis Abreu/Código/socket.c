//
//  socket.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "socket.h"

struct sockaddr_in socket_addr(char* ip, int port) {
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_aton(ip, &addr.sin_addr);
    return addr;
}

void socket_write(socketfd s, byte* bytes, int size) {
    for (long pos = 0; pos < size;) {
        pos += write(s, bytes + pos, size - pos);
    }
}

bool socket_read(socketfd s, byte* buffer, int size) {
    long bytes_read;
    for (long pos = 0; pos < size; pos += bytes_read) {
        bytes_read = read(s, buffer + pos, size - pos);
        
        if (bytes_read <= 0) {
            return true;
        }
    }
    
    return false;
}

void socket_close(socketfd s) {
    close(s);
}
