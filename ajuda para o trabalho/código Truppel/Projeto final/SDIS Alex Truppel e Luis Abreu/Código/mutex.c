//
//  mutex.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#include "mutex.h"

void mutex_new(mutex_t* m) {
    int res = pthread_mutex_init(m, NULL);
    xassert(res == 0, "Error creating mutex");
}

void mutex_free(mutex_t* m) {
    int res = pthread_mutex_destroy(m);
    xassert(res == 0, "Error destroying mutex");
}

void mutex_lock(mutex_t* m) {
    int res = pthread_mutex_lock(m);
    xassert(res == 0, "Error locking mutex");
}

void mutex_unlock(mutex_t* m) {
    int res = pthread_mutex_unlock(m);
    xassert(res == 0, "Error unlocking mutex");
}
