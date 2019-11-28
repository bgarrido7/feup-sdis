//
//  producer.c
//  SDIS Teste
//
//  Created by Alexandre on 10/01/2018.
//  Copyright © 2018 XYZ. All rights reserved.
//

#include <stdio.h>
#include "socket.h"

// gcc producer.c socket.c -o producer
int main(int argc, char *argv[]) {
	if (argc < 4) {
        printf("Arguments missing\n");
		exit(-1);
	}
    
	char* ip = argv[1];
	int port = atoi(argv[2]);

    sfd sock = s_udp();
	
    for (int i = 3; i < argc; i++) {
        float v = atof(argv[i]);
        int32_t v_int = v * 100000; // Assumindo que: int32_min > temp * 100000 > int32_max
        s_write_addr(sock, (byte*)&v_int, 4, s_addr(ip, port));
        printf("Producer: sent message, value = %f\n", v);
        sleep(1);
    }
    
    s_close(sock);
}
