//
//  workerpool.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "workerpool.h"

typedef struct {
    void (*func)(void*);
    void* info;
} workerpool_workitem_t;

void* workerpool_thread_function(void* info) {
    printf("Worker thread started\n");

    workerpool_t* wp = (workerpool_t*)info;
    while (1) {
        
        // Wait for a new workitem to be added to the queue
        signal_wait(&(wp->new_items_signal));
        
        // Get next code block and execute while there are blocks to execute. No blocks available -> wait for signal
        workerpool_workitem_t* item;
        do {
            // Get work item
            mutex_lock(&(wp->queue_mutex));
            
            if (wp->use_priority) {
                item = heap_remove_head(&(wp->priority_queue));
            }
            else {
                item = queue_pop(&(wp->fifo_queue));
            }
            
            mutex_unlock(&(wp->queue_mutex));
            
            // Execute work item
            if (item) {
                item->func(item->info);
                free(item);
            }
        } while (item);
    }
    
    return NULL;
}

void workerpool_new(workerpool_t* wp, int thread_count, bool use_priority, int max_queue_size) {
    // Create objects
    mutex_new(&(wp->queue_mutex));
    signal_new(&(wp->new_items_signal));
    
    if (use_priority) {
        bool res = heap_new(&(wp->priority_queue), max_queue_size);
        xassert(res, "Could not allocate heap");
    }
    else {
        queue_new(&(wp->fifo_queue));
    }
    
    wp->use_priority = use_priority;
    wp->threads = (thread_t*)calloc(thread_count, sizeof(thread_t));
    
    // Start threads
    for (int i = 0; i < thread_count; i++) {
        wp->threads[i] = thread_spawn(workerpool_thread_function, (void*)wp);
    }
}

void workerpool_free() {
    // TODO
    // Stop threads
    // Remove and free all items in queue
    // ...?
    
    // Not implemented because this object is never freed in this program, so...
}

void workerpool_enqueue(workerpool_t* wp, void (*func)(void*), void* info, int priority) {
    // Create item
    workerpool_workitem_t* item = malloc(sizeof(workerpool_workitem_t));
    item->func = func;
    item->info = info;
    
    // Add item
    mutex_lock(&(wp->queue_mutex));
    
    if (wp->use_priority) {
        heap_insert(&(wp->priority_queue), item, priority);
    }
    else {
        queue_push(&(wp->fifo_queue), item);
    }
    
    mutex_unlock(&(wp->queue_mutex));
    
    // Signal threads a new item is avaliable
    signal_send(&(wp->new_items_signal));
}
