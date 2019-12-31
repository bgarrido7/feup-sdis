//
//  signal.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef signal_h
#define signal_h

#include "general.h"
#include "mutex.h"

typedef struct {
    mutex_t m;
    pthread_cond_t c;
} signal_t;

void signal_new(signal_t* signal);
void signal_free(signal_t* signal);
void signal_wait(signal_t* signal);
void signal_send(signal_t* signal);

#endif /* signal_h */
