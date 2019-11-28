//
//  workerpool.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef workerpool_h
#define workerpool_h

#include <stdio.h>
#include "general.h"
#include "queue.h"
#include "heap.h"
#include "mutex.h"
#include "thread.h"
#include "signal.h"

typedef struct {
    heap_t priority_queue;
    queue_t fifo_queue;
    mutex_t queue_mutex;
    signal_t new_items_signal;
    thread_t* threads;
    bool use_priority;
} workerpool_t;

void workerpool_new(workerpool_t* wp, int thread_count, bool use_priority, int max_queue_size);
//void workerpool_free();
void workerpool_enqueue(workerpool_t* wp, void (*func)(void*), void* info, int priority);

#endif /* workerpool_h */
