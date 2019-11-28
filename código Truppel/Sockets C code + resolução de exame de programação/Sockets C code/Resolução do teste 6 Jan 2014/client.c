//
//  client.c
//  SDIS Teste
//
//  Created by Alexandre on 10/01/2018.
//  Copyright © 2018 XYZ. All rights reserved.
//

#include <stdio.h>
#include "socket.h"

// gcc client.c socket.c -o client
int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Arguments missing\n");
		exit(-1);
	}

	char* ip = argv[1];
	int port = atoi(argv[2]);
    
    sfd client_socket = s_tcp();
    s_connect(client_socket, s_addr(ip, port));

    int32_t temp_int;
    s_read(client_socket, (byte*)(&temp_int), 4);
    printf("Client: received message, value = %f\n", temp_int / 100000.0);
    
    s_close(client_socket);
}
