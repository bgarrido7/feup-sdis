//
//  signal.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "signal.h"

void signal_new(signal_t* signal) {
    mutex_new(&(signal->m));
    int res = pthread_cond_init(&(signal->c), NULL);
    xassert(res == 0, "Error creating condition variable");
}

void signal_free(signal_t* signal) {
    mutex_free(&(signal->m));
    int res = pthread_cond_destroy(&(signal->c));
    xassert(res == 0, "Error destroying condition variable");
}

void signal_wait(signal_t* signal) {
    mutex_lock(&(signal->m));
    int res = pthread_cond_wait(&(signal->c), &(signal->m));
    xassert(res == 0, "Error waiting for condition variable");
    mutex_unlock(&(signal->m));
}

void signal_send(signal_t* signal) {
    mutex_lock(&(signal->m));
    int res = pthread_cond_signal(&(signal->c));
    xassert(res == 0, "Error signaling condition variable");
    mutex_unlock(&(signal->m));
}
