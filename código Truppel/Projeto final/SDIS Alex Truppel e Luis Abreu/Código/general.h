//
//  general.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef general_h
#define general_h

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef uint8_t byte;
typedef struct timeval timestamp_t;
#define xassert(cond, error) { if (!(cond)) { printf("%s\n", (error)); assert((cond)); } }
#define time_interval(start, end) (((end).tv_sec - (start).tv_sec) + ((end).tv_usec - (start).tv_usec) / 1000000.0)
#define time_stamp(v) { gettimeofday(&(v), NULL); }
#define rand(min, max) (arc4random_uniform((max) - (min)) + (min))
#define open_file(variable, path, mode) FILE* variable; do { variable = fopen((path), (mode)); } while ((variable) == NULL);

// MARK: - Server settings
#define SERVER_TEST_WITH_TCP 0
#define SERVER_USE_GCD 1

#define SERVER_IP "localhost"
#define SERVER_PORT 4444
#define LISTEN_BUFFER_SIZE 5000

#define WORKERPOOL_THREAD_COUNT 8
#define WORKERPOOL_MAX_ITEM_COUNT 1000000
#define WORKERPOOL_USE_PRIORITY 0

#define DATA_FILE_PATH "/Users/Alex/Documents/Alexandre/FEUP/5 Ano/SDIS/Projeto/SDIS/SDIS/data" // head -c 1048576 < /dev/urandom > data
#define DATA_FILE_SIZE (1024 * 1024)
#define DATA_FILE_READ_SIZE 80000 // in bytes

#define RESULTS_FILE_PATH "/Users/Alex/Documents/Alexandre/FEUP/5 Ano/SDIS/Projeto/SDIS/SDIS/results.txt"

// MARK: - Client settings
#define CLIENT_SPAWN_COUNT 2000

#endif /* general_h */

/*
 A = nº blocos executados desde a recepção do cliente até atender totalmente o cliente
 B = tempo para atender totalmente o cliente
 C = nº de clientes pendentes aquando a recepção deste cliente
 D = nº de clientes pendentes aquando a finalização deste cliente
 E = (C + D) / 2
 F = A / B

 x = A
 y = B
 
 x = E
 y = B
 
 x = E
 y = F
*/
