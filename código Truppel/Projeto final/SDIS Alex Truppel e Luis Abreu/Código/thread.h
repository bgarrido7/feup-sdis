//
//  thread.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef thread_h
#define thread_h

#include "general.h"

typedef pthread_t thread_t;

thread_t thread_spawn(void* (*function)(void*), void* info);
void thread_wait(thread_t thread);

#endif /* thread_h */
