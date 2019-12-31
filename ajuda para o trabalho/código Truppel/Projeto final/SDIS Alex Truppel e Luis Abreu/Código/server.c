//
//  server.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "server.h"

typedef struct {
    server_t* server;
    clientconn_t client;
    
    // Stats info
    timestamp_t start_time;
    int start_clients_pending_count;
    int start_blocks_executed_count;
} server_client_run_info_t;

void server_client_run_info_start(server_t* server, socketfd socket);
void server_client_run_info_dispatch(server_client_run_info_t* info);
void server_client_run_info_finished(server_client_run_info_t* info);

void* server_threadbased_clientconn_run_all(void* info);
void server_eventdriven_clientconn_run_next(void* info);

void server_init(server_t* server, ipaddr ip, int port, server_mode_t mode) {
    
    // Create socket
    server->socket = socket(PF_INET, SOCK_STREAM, 0);
    xassert(server->socket >= 0, "Error creating socket");
    
    int optval = 1;
    setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
    struct sockaddr_in serv_addr = socket_addr(ip, port);
    int res = bind(server->socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    xassert(res >= 0, "Error binding to socket");

    res = listen(server->socket, LISTEN_BUFFER_SIZE);
    xassert(res != -1, "Error setting listen value");

    // Set server mode
    server->mode = mode;
    
    // Init other variables
    server->blocks_executed_count = 0;
    mutex_new(&server->blocks_executed_count_mutex);
    
    server->clients_pending_count = 0;
    mutex_new(&server->clients_pending_count_mutex);
    
    // Create workerpool if necessary
    if (server->mode == EVENTS_CUSTOM) {
        workerpool_new(&(server->workerpool), WORKERPOOL_THREAD_COUNT, WORKERPOOL_USE_PRIORITY, WORKERPOOL_MAX_ITEM_COUNT);
    }
#if SERVER_USE_GCD
    else if (server->mode == EVENTS_GCD) {
        server->gcd_queue = dispatch_queue_create("Server concurrent queue", DISPATCH_QUEUE_CONCURRENT);
    }
#endif
}

void server_run(server_t* server) {
    printf("Server started\n");
    
    while (1) {
        
        // Get new connection
        struct sockaddr_in cli_addr;
        socklen_t client_addr_length = sizeof(cli_addr);
        
        socketfd new_socket = accept(server->socket, (struct sockaddr *) &cli_addr, &client_addr_length);
        if (new_socket == -1) { break; }
        
        // Process connection
        server_client_run_info_start(server, new_socket);
    }
    
    printf("Server stopped\n");
}

void server_inject(server_t* server) {
    server_client_run_info_start(server, 0);
}

void server_blocks_executed_count_increment(server_t* server) {
    mutex_lock(&server->blocks_executed_count_mutex);
    server->blocks_executed_count++;
    mutex_unlock(&server->blocks_executed_count_mutex);
}
int server_blocks_executed_count_get(server_t* server) {
    int count;
    mutex_lock(&server->blocks_executed_count_mutex);
    count = server->blocks_executed_count;
    mutex_unlock(&server->blocks_executed_count_mutex);
    return count;
}

void server_clients_pending_count_add(server_t* server, int delta) {
    mutex_lock(&server->clients_pending_count_mutex);
    server->clients_pending_count += delta;
    mutex_unlock(&server->clients_pending_count_mutex);
}
int server_clients_pending_count_get(server_t* server) {
    int count;
    mutex_lock(&server->clients_pending_count_mutex);
    count = server->clients_pending_count;
    mutex_unlock(&server->clients_pending_count_mutex);
    return count;
}

void server_client_run_info_start(server_t* server, socketfd socket) {
    server_client_run_info_t* info = malloc(sizeof(server_client_run_info_t));
    
    // Create client and increment counter
    info->server = server;
    clientconn_init(&(info->client), socket);
    server_clients_pending_count_add(server, 1);
    
    // Record start time and number of processes already submitted
    time_stamp(info->start_time)
    info->start_blocks_executed_count = server_blocks_executed_count_get(server);
    info->start_clients_pending_count = server_clients_pending_count_get(server);
    
    // Dispatch client code
    server_client_run_info_dispatch(info);
}
void server_client_run_info_dispatch(server_client_run_info_t* info) {
    if (info->server->mode == THREADS) {
        thread_spawn(server_threadbased_clientconn_run_all, info);
    }
    else if (info->server->mode == EVENTS_CUSTOM) {
        workerpool_enqueue(&(info->server->workerpool), server_eventdriven_clientconn_run_next, info, 0);
    }
#if SERVER_USE_GCD
    else if (info->server->mode == EVENTS_GCD) {
        dispatch_async(info->server->gcd_queue, ^{
            server_eventdriven_clientconn_run_next(info);
        });
    }
#endif
}
void server_client_run_info_finished(server_client_run_info_t* info) {
    
    // Decrement client pending counter
    server_clients_pending_count_add(info->server, -1);
    
    // Get delta time
    timestamp_t end;
    time_stamp(end)
    double interval = time_interval(info->start_time, end);
    
    int A = server_blocks_executed_count_get(info->server) - info->start_blocks_executed_count;
    double B = interval;
    int C = info->start_clients_pending_count;
    int D = server_clients_pending_count_get(info->server);
    double E = (C + D) / 2;
    double F = A / B;
    
    // Save info
    open_file(fd, RESULTS_FILE_PATH, "a")
    fprintf(fd, "%d %f %d %d %f %f\n", A, B, C, D, E, F);
    fclose(fd);
    
    free(info);
}

void* server_threadbased_clientconn_run_all(void* info) {
    bool done;
    do {
        done = clientconn_run_next(&(((server_client_run_info_t*)info)->client));
        server_blocks_executed_count_increment(((server_client_run_info_t*)info)->server);
    } while(!done);
    
    server_client_run_info_finished((server_client_run_info_t*)info);
    return NULL;
}
void server_eventdriven_clientconn_run_next(void* info) {
    bool done = clientconn_run_next(&(((server_client_run_info_t*)info)->client));
    server_blocks_executed_count_increment(((server_client_run_info_t*)info)->server);

    if (done) {
        server_client_run_info_finished(((server_client_run_info_t*)info));
    }
    else {
        server_client_run_info_dispatch(((server_client_run_info_t*)info));
    }
}
