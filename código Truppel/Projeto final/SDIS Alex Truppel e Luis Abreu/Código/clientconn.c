//
//  clientconn.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "clientconn.h"
#include "server.h"

// MARK: - Defines

#define CLIENTCONN_PROCESS_COUNT 5

void clientconn_process_read_request(clientconn_t* client);
void clientconn_process_read_file(clientconn_t* client);
void clientconn_process_calculate_hash(clientconn_t* client);
void clientconn_process_write_file(clientconn_t* client);
void clientconn_process_close_conn(clientconn_t* client);

typedef void (*clientconn_process_f)(clientconn_t* client);
clientconn_process_f clientconn_processes[CLIENTCONN_PROCESS_COUNT] = {
    clientconn_process_read_request, clientconn_process_read_file, clientconn_process_calculate_hash, clientconn_process_write_file, clientconn_process_close_conn,
};

// MARK: - Main functions

void clientconn_init(clientconn_t* client, socketfd socket) {
    client->socket = socket;
    client->next_process = 0;
}

// Returns true if done
bool clientconn_run_next(clientconn_t* client) {
    
    // If done, do nothing and return true
    if (client->next_process >= CLIENTCONN_PROCESS_COUNT) { return true; }
    
    // If not done, run process and increment index
    clientconn_processes[client->next_process](client);
    client->next_process++;
    
    // Return true if done
    return client->next_process == CLIENTCONN_PROCESS_COUNT;
}

// MARK: - Client processes

void clientconn_process_read_request(clientconn_t* client) {
#if SERVER_TEST_WITH_TCP
    socket_read(client->socket, (uint8_t*)&(client->read_position), sizeof(client->read_position));
#else
    client->read_position = arc4random_uniform(DATA_FILE_SIZE - DATA_FILE_READ_SIZE);
#endif
}

void clientconn_process_read_file(clientconn_t* client) {
    for (int i = 0; i < 1000; i++) {
        
        open_file(fd, DATA_FILE_PATH, "r+b")
        fseek(fd, client->read_position, SEEK_SET);
        fread(&(client->file_bytes), DATA_FILE_READ_SIZE, 1, fd);
        fclose(fd);
        
    }
}

void clientconn_process_calculate_hash(clientconn_t* client) {
    for (int i = 0; i < 1000; i++) {
        
        client->result = 0x00;
        for (int i = 0; i < DATA_FILE_READ_SIZE; i++) {
            client->result ^= client->file_bytes[i];
        }
        
    }
}

void clientconn_process_write_file(clientconn_t* client) {
    for (int i = 0; i < 1000; i++) {
        
        open_file(fd, DATA_FILE_PATH, "r+b")
        fseek(fd, client->read_position, SEEK_SET);
        fwrite(&(client->result), 1, 1, fd);
        fclose(fd);
        
    }
}

void clientconn_process_close_conn(clientconn_t* client) {
#if SERVER_TEST_WITH_TCP
    socket_write(client->socket, &client->result, 1);
#endif
}
