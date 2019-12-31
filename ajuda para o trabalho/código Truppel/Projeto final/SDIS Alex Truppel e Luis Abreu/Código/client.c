//
//  client.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "client.h"

socketfd client_connect(ipaddr ip, int port);
void client_request(socketfd socket);

void* client_run(void* x) {
    int i = (int)x;
    timestamp_t s, e;
    
    time_stamp(s);
    client_request(client_connect(SERVER_IP, SERVER_PORT));
    time_stamp(e);
    
    printf("Client %d ended.\tWaited %f secs\n", i, time_interval(s, e));
    
    return NULL;
}

socketfd client_connect(ipaddr ip, int port) {
    socketfd sock = socket(PF_INET, SOCK_STREAM, 0);
    xassert(sock >= 0, "Error creating socket");
    
    struct sockaddr_in serv_addr = socket_addr(ip, port);
    int res = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    xassert(res >= 0, "Error connecting to socket");
    
    return sock;
}

void client_request(socketfd socket) {
    
    // Request file position
    uint64_t read_position = arc4random_uniform(DATA_FILE_SIZE - DATA_FILE_READ_SIZE);
    socket_write(socket, (uint8_t*)&read_position, sizeof(read_position));
    
    // Wait for result
    byte b[1];
    socket_read(socket, b, 1); // Wait for server to finish
    socket_close(socket);
}
