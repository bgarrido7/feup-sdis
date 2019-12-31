//
//  main.c
//  SDIS Teste
//
//  Created by Alexandre on 10/01/2018.
//  Copyright © 2018 XYZ. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "socket.h"

// ----------
// TCP server
// ----------
void tcp_server() {
    char* ip = "localhost";
    int port = 5555;
    
    sfd server_socket = s_tcp(); // Create server socket
    s_reuse(server_socket); // Enable option to reuse server address
    s_bind(server_socket, s_addr(ip, port)); // Bind this socket to the server address
    s_listen(server_socket, 5);
    
    // Run server in infinite loop
    while (1) {
        sfd new_socket = s_accept(server_socket);
        if (new_socket == -1) { break; }
        
        // USE s_read & s_write ON new_socket HERE
    }
    
    s_close(server_socket);
}

// ----------
// TCP CLIENT
// ----------
void tcp_client() {
    char* ip = "localhost";
    int port = 5555;
    
    sfd client_socket = s_tcp(); // Create socket
    s_connect(client_socket, s_addr(ip, port)); // Connect to server address
    
    // USE s_read & s_write HERE
    
    s_close(client_socket);
}

// ----------
// UDP SENDER UNI & MULTI CAST
// ----------
void udp_sender() {
    // Create sender addresses
    sa sender_addr = s_addr("localhost", 5555);
    
    // Create receiver address (ip can be uni or multi cast address)
    // The receiver sockets must bind to this port (and also this ip if this is unicast)
    sa receiver_addr = s_addr("225.0.0.37", 6666);
    
    // Create socket
    sfd sock = s_udp();
    
    // Force this socket to use this ip/port (if necessary)
    s_reuse(sock);
    s_bind(sock, sender_addr);
    
    // USE s_write_addr WITH receiver_addr HERE
    // Example:
    while (1) {
        char* message = "Hello, World!";
        s_write_addr(sock, (byte*)message, (int)strlen(message) + 1, receiver_addr);
        printf("Sent message\n");
        sleep(1);
    }
    
    s_close(sock);
}

// ----------
// UDP RECEIVER UNI & MULTI CAST
// ----------
void udp_consumer(int is_multicast) {
    // Create addresses
    sa sender_addr;
    sa receiver_addr;
    
    if (is_multicast) {
        sender_addr = s_addr("0:0:0:0", 0); // It appears that the sender's ip and port do not matter in this case
        receiver_addr = s_addr("0:0:0:0", 6666); // 0:0:0:0 = INADDR_ANY, port is the receiver's port (the port to which UDP packets are sent)
    }
    else {
        sender_addr = s_addr("localhost", 5555);
        receiver_addr = s_addr("localhost", 6666);
    }
    
    // Create socket
    sfd sock = s_udp();
    
    // Force this socket to use this port
    s_reuse(sock);
    s_bind(sock, receiver_addr);
    
    // Join multicast group if multicast
    if (is_multicast) {
        s_multicast(sock, "225.0.0.37");
    }
    
    // USE s_read_addr WITH sender_addr HERE
    // Example:
    while (1) {
        char message[256];
        s_read_addr(sock, (byte*)message, 256, sender_addr);
        printf("Got message = '%s'\n", message);
    }
    
    s_close(sock);
}

// gcc examples.c socket.c -o examples
int main(int argc, const char * argv[]) {
    if (atoi(argv[1])) { udp_sender(); }
    else { udp_consumer(1); }
}

