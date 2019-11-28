//
//  mutex.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef mutex_h
#define mutex_h

#include "general.h"

typedef pthread_mutex_t mutex_t;

void mutex_new(mutex_t* m);
void mutex_free(mutex_t* m);
void mutex_lock(mutex_t* m);
void mutex_unlock(mutex_t* m);

#endif /* mutex_h */
