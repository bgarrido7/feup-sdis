//
//  consumer.c
//  SDIS Teste
//
//  Created by Alexandre on 10/01/2018.
//  Copyright © 2018 XYZ. All rights reserved.
//

#include <stdio.h>
#include "socket.h"

// gcc consumer.c socket.c -o consumer
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Arguments missing\n");
        exit(-1);
    }
    
    char* ip = argv[1];
    int port = atoi(argv[2]);
    
    sfd sock = s_udp();
    s_reuse(sock);
    s_bind(sock, s_addr("0:0:0:0", port));
    s_multicast(sock, ip);

    while (1) {
        int32_t v_int;
        s_read_addr(sock, (byte*) &v_int, 4, s_addr("0:0:0:0", 0));
        printf("Consumer: received message, value = %f\n", v_int / 100000.0);
    }
    
    s_close(sock);
}
