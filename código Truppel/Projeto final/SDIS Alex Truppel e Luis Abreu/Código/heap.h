//
//  heap.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include "general.h"

typedef struct {
    int priority;
    void* value;
} heap_element_t;

typedef struct {
    int current_size;
    int max_size;
    heap_element_t** elements;
} heap_t;

bool heap_new(heap_t* h, int max_size);
void heap_free(heap_t* heap);
bool heap_insert(heap_t* heap, void* value, int priority); // Lower value means higher priority, does not keep fifo order if all elements have the same priority
void* heap_remove_head(heap_t* heap);

#endif /* heap_h */
