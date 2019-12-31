//
//  server.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef server_h
#define server_h

#include "general.h"
#include "socket.h"
#include "clientconn.h"
#include "thread.h"
#include "workerpool.h"

#if SERVER_USE_GCD
#include <dispatch/dispatch.h>
#endif

typedef enum {
    THREADS = 0,
    EVENTS_CUSTOM = 1,
#if SERVER_USE_GCD
    EVENTS_GCD = 2
#endif
} server_mode_t;

typedef struct {
    socketfd socket;
    
    server_mode_t mode;
    workerpool_t workerpool;
#if SERVER_USE_GCD
    dispatch_queue_t gcd_queue;
#endif
    
    int clients_pending_count; mutex_t clients_pending_count_mutex;
    int blocks_executed_count; mutex_t blocks_executed_count_mutex;
} server_t;

void server_init(server_t* server, ipaddr ip, int port, server_mode_t mode);
void server_run(server_t* server);
void server_inject(server_t* server);

#endif /* server_h */
