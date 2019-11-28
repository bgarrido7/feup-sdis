//
//  main.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "general.h"
#include "server.h"

#define N_CICLES 5

int main(int argc, const char * argv[]) {
    int server_mode = atoi(argv[1]);
    int min_wait_us = atoi(argv[2]);
    int max_wait_us = atoi(argv[3]);
    
    server_t server;
    server_init(&server, SERVER_IP, SERVER_PORT, server_mode);
    
#if SERVER_TEST_WITH_TCP
    server_run(&server);
#else
    for (int i = 0; i < CLIENT_SPAWN_COUNT; i++) {
        server_inject(&server);
        
        double wave = (sin( (double)i / CLIENT_SPAWN_COUNT * N_CICLES * (M_PI * 2)) + 1) / 2.0;
        usleep(wave * (max_wait_us - min_wait_us) + min_wait_us);
    }
    
    sleep(10000);
#endif
    
    return 0;
}
