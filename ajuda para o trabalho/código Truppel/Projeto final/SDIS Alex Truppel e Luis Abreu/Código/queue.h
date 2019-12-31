//
//  queue.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include "general.h"

typedef struct _queue_item_t {
    void* value;
    struct _queue_item_t* next;
} queue_item_t;

typedef struct {
    int size;
    queue_item_t* head;
    queue_item_t* tail;
} queue_t;

void queue_new(queue_t* queue);
void queue_free(queue_t* q);
void queue_push(queue_t* q, void* value);
void* queue_pop(queue_t* q);
int queue_size(queue_t* q);

#endif
