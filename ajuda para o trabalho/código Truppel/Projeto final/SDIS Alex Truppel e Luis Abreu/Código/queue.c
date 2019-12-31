//
//  queue.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "queue.h"

void queue_new(queue_t* queue) {
    queue->size = 0;
	queue->head = NULL;
    queue->tail = NULL;
}

void queue_free(queue_t* q) {
    queue_item_t* obj = q->head;
    queue_item_t* aux;
    
    while (obj) {
        aux = obj->next;
        free(obj);
        obj = aux;
    }
}

void queue_push(queue_t* q, void* value) {
    if (!q || !value) return;
    
    queue_item_t* obj = malloc(sizeof(queue_item_t));
    xassert(obj, "Out of memory, cannot push value onto queue");
    
    obj->value = value;
    obj->next = NULL;
    
    if (q->tail) q->tail->next = obj;
    if (!q->head) q->head = obj;
    
    q->tail = obj;
    q->size++;
}

void* queue_pop(queue_t* q) {
    if (!q) return NULL;
    if (!q->head) return NULL;
    
    queue_item_t* obj = q->head;
    void* value = obj->value;
    
    q->head = obj->next;
    if (q->tail == obj) q->tail = NULL;
    free(obj);
    
    q->size--;
    return value;
}

int queue_size(queue_t* q) {
    return q ? q->size : -1;
}
