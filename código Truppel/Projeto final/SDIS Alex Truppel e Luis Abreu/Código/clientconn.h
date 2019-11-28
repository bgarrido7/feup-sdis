//
//  clientconn.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef clientconn_h
#define clientconn_h

#include "general.h"
#include "socket.h"

typedef struct {
    // Conn info
    socketfd socket;
        
    // State machine
    int next_process;
    uint64_t read_position;
    byte file_bytes[DATA_FILE_READ_SIZE];
    byte result;
} clientconn_t;

void clientconn_init(clientconn_t* client, socketfd socket);
bool clientconn_run_next(clientconn_t* client); // Returns true if done

#endif /* clientconn_h */
