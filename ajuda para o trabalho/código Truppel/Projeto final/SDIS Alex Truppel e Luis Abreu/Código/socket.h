//
//  socket.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 Alex & Luis. All rights reserved.
//

#ifndef socket_h
#define socket_h

#include "general.h"

typedef int socketfd;
typedef char* ipaddr;

struct sockaddr_in socket_addr(ipaddr ip, int port);
void socket_write(socketfd s, byte* bytes, int size);
bool socket_read(socketfd s, byte* buffer, int size);
void socket_close(socketfd s);

#endif /* socket_h */
