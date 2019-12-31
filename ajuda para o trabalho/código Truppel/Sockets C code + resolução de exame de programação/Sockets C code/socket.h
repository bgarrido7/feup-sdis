//
//  socket.h
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 XYZ. All rights reserved.
//

#ifndef socket_h
#define socket_h

#include <stdio.h>
#include <assert.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

typedef uint8_t byte;
typedef int sfd;
typedef char* ipa;
typedef struct sockaddr_in sa;

sfd s_tcp();
sfd s_udp();
sa s_addr(ipa ip, int port);
void s_reuse(sfd s);
void s_multicast(sfd s, ipa ip_group);
void s_listen(sfd s, int c);
void s_connect(sfd s, sa addr);
void s_bind(sfd s, sa addr);
sfd s_accept(sfd s);
void s_write(sfd s, byte* bytes, int size);
int s_read(sfd s, byte* buffer, int size);
void s_write_addr(sfd s, byte* bytes, int size, sa addr);
long s_read_addr(sfd s, byte* buffer, int size, sa addr);
void s_close(sfd s);

#endif /* socket_h */
