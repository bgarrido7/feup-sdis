//
//  server.c
//  SDIS Teste
//
//  Created by Alexandre on 10/01/2018.
//  Copyright © 2018 XYZ. All rights reserved.
//

#include <stdio.h>
#include "socket.h"

// gcc server.c socket.c -o server
int main(int argc, char* argv[]) {
	if (argc < 3) {
        printf("Arguments missing\n");
		exit(-1);
	}

	char* ip = "localhost";
	int port = atoi(argv[1]);
	float temp = atof(argv[2]);
    
    sfd server_socket = s_tcp();
    s_reuse(server_socket);
    s_bind(server_socket, s_addr(ip, port));
    s_listen(server_socket, 5);
    
    while (1) {
        sfd new_socket = s_accept(server_socket);
        if (new_socket == -1) { break; }
        
        int32_t temp_int = temp * 100000; // Assumindo que: int32_min > temp * 100000 > int32_max
        s_write(new_socket, (byte*)(&temp_int), 4);
        printf("Server sent message, value = %f\n", temp);
    }
    
    s_close(server_socket);
}
