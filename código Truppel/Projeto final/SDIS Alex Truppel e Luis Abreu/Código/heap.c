//
//  heap.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "heap.h"

#define RAIZ 			(0)
#define PAI(x) 			((x-1)/2)
#define FILHO_ESQ(x) 	((x*2)+1)
#define FILHO_DIR(x) 	((x*2)+2)

bool heap_element_compare_e1_bigger_priority_than_e2(heap_element_t* e1, heap_element_t* e2);

bool heap_new(heap_t* h, int max_size) {
    h->current_size = 0;
    h->max_size = max_size;
    h->elements = (heap_element_t**)calloc(max_size, sizeof(heap_element_t*));
    
    if (!h->elements) {
        free(h);
        return false;
    }
    
    return true;
}

void heap_free(heap_t*h) {
    if (!h) { return; }
    
    for (int i = 0; i < h->current_size; i++) {
        free(h->elements[i]);
        h->elements[i] = NULL;
    }
    
    free(h->elements);
}


heap_element_t* heap_create_element(int priority, void* value) {
    heap_element_t* elem = (heap_element_t*) malloc(sizeof(heap_element_t));
    if (!elem) { return NULL; }
    
    elem->value = value;
    elem->priority = priority;
    
    return elem;
}


bool heap_insert(heap_t* h, void* value, int priority) {
    heap_element_t* aux;
    heap_element_t* elem;
    
    /* se heap esta' cheia, nao insere elemento */
    if (h->current_size >= h->max_size) {
        return false;
    }
    
    elem = heap_create_element(priority, value);
    if (!elem) {
        return false;
    }
    
    /* coloca elemento no fim da heap */
    int i = h->current_size;
    h->elements[i] = elem;
    h->current_size++;
    
    /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
    while (i != RAIZ && heap_element_compare_e1_bigger_priority_than_e2(h->elements[i], h->elements[PAI(i)])) {
        aux = h->elements[PAI(i)];
        h->elements[PAI(i)] = h->elements[i];
        h->elements[i] = aux;
        i = PAI(i);
    }
    
    return true;
}


void* heap_remove_head(heap_t* h) {
    int i, filho_maior;
    heap_element_t* aux;
    void* value;
    
    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->current_size <= 0) {
        return NULL;
    }
    
    value = h->elements[RAIZ]->value;
    free(h->elements[RAIZ]);
    
    /* coloca ultimo elemento da heap na raiz */
    h->current_size--;
    h->elements[RAIZ] = h->elements[h->current_size];
    h->elements[h->current_size] = NULL;
    
    i = RAIZ;
    
    /* enquanto nao chegar 'a base da heap */
    while (FILHO_ESQ(i) < h->current_size) {
        filho_maior = FILHO_ESQ(i);
        
        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) < h->current_size && heap_element_compare_e1_bigger_priority_than_e2(h->elements[FILHO_DIR(i)], h->elements[FILHO_ESQ(i)])) {
            filho_maior = FILHO_DIR(i);
        }
        
        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (heap_element_compare_e1_bigger_priority_than_e2(h->elements[filho_maior], h->elements[i])) {
            aux = h->elements[filho_maior];
            h->elements[filho_maior] = h->elements[i];
            h->elements[i] = aux;
            i = filho_maior;
        }
        else {
            break;
        }
    }
    
    return value;
}

bool heap_element_compare_e1_bigger_priority_than_e2(heap_element_t* e1, heap_element_t* e2) {
    if (e1 == NULL || e2 == NULL)  {
        return false;
    }
    
    return e1->priority < e2->priority;
}

