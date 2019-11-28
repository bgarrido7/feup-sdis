//
//  socket.c
//  SDIS
//
//  Created by Alexandre on 01/12/2017.
//  Copyright © 2017 XYZ. All rights reserved.
//

#include "socket.h"

sfd s_tcp() {
    sfd s = socket(PF_INET, SOCK_STREAM, 0);
    assert(s >= 0);
    return s;
}

sfd s_udp() {
    sfd s = socket(PF_INET, SOCK_DGRAM, 0);
    assert(s >= 0);
    return s;
}

sa s_addr(ipa ip, int port) {
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);
    return addr;
}

void s_reuse(sfd s) {
    int optval = 1;
    int res = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    assert(res >= 0);
}

void s_multicast(sfd s, ipa ip_group) {
    struct ip_mreq mreq;
    inet_pton(AF_INET, ip_group, &mreq.imr_multiaddr.s_addr);
    inet_pton(AF_INET, "0:0:0:0", &mreq.imr_interface.s_addr); // 0:0:0:0 = INADDR_ANY
    
    int res = setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    assert(res >= 0);
}

void s_listen(sfd s, int c) {
    int res = listen(s, c);
    assert(res != -1);
}

void s_connect(sfd s, sa addr) {
    int res = connect(s, (struct sockaddr *) &addr, sizeof(addr));
    assert(res >= 0);
}

void s_bind(sfd s, sa addr) {
    int res = bind(s, (struct sockaddr *) &addr, sizeof(addr));
    assert(res >= 0);
}

sfd s_accept(sfd s) {
    sa cli_addr;
    socklen_t client_addr_length = sizeof(cli_addr);
    return accept(s, (struct sockaddr *) &cli_addr, &client_addr_length);
}

void s_write(sfd s, byte* bytes, int size) {
    for (long pos = 0; pos < size;) {
        pos += write(s, bytes + pos, size - pos);
    }
}

int s_read(sfd s, byte* buffer, int size) {
    long bytes_read;
    for (long pos = 0; pos < size; pos += bytes_read) {
        bytes_read = read(s, buffer + pos, size - pos);
        
        if (bytes_read <= 0) {
            return 0;
        }
    }
    
    return 1;
}

long s_read_addr(sfd s, byte* buffer, int size, sa addr) {
    socklen_t addr_length = sizeof(addr);
    return recvfrom(s, buffer, size, 0, (struct sockaddr *) &addr, &addr_length);
}

void s_write_addr(sfd s, byte* bytes, int size, sa addr) {
    sendto(s, bytes, size, 0, (struct sockaddr *) &addr, sizeof(addr));
}

void s_close(sfd s) {
    close(s);
}
