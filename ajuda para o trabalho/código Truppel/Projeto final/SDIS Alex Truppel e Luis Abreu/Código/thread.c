//
//  thread.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "thread.h"

thread_t thread_spawn(void* (*function)(void*), void* info) {
    thread_t thread;
    int res = pthread_create(&thread, NULL, function, info);
    
    if (res != 0) { printf("Error creating thread\n"); }
    //xassert(res == 0, "Error creating thread");
    return thread;
}

void thread_wait(thread_t thread) {
    int res = pthread_join(thread, NULL);
    xassert(res == 0, "Error waiting on thread");
}

void thread_kill(thread_t thread) {
    //pthread_kill(thread, int);
}
