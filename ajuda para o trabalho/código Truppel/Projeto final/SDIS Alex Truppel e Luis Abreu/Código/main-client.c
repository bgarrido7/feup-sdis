//
//  main-client.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "general.h"
#include "client.h"
#include "thread.h"

int main(int argc, const char * argv[]) {
    thread_t t[CLIENT_SPAWN_COUNT];
    
    while (1) {
        client_request(client_connect(SERVER_IP, SERVER_PORT));
        usleep(10);
    }

    for (int i = 0; i < CLIENT_SPAWN_COUNT; i++) {
        t[i] = thread_spawn(client_run, (void*)i);
        usleep(10);
    }
    
    for (int i = 0; i < CLIENT_SPAWN_COUNT; i++) {
        thread_wait(t[i]);
    }
    
    printf("All clients done\n");
    
    sleep(10000); // Give time to read values in the console
    return 0;
}
