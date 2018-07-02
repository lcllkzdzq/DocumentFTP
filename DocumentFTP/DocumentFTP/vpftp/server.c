//
//  server.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/21.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "server.h"
#include "connection.h"
#include "sysapi.h"
#include <string.h>
#include "string.h"

void vpftp_server_init(vpftp_server_ptr server, int port, const char *path) {
    server->socket = 0;
    server->port = port;
    
    for (int i = 0; i < VPFTP_MAX_CONNECTION; ++i) {
        server->connection[i] = NULL;
    }
    
    server->accept_connect = 0;
    server->maxfd = 0;
    
    server->thread = NULL;
    FD_ZERO(&server->active_set);
    
    server->access = (vptfp_access_ptr)vpftp_malloc(sizeof(vptfp_access));
    vpftp_access_init(server->access);
    
    server->home = vpftp_string_copy(path);
}

void vpftp_server_free(vpftp_server_ptr server) {
    for (int i = 0; i < VPFTP_MAX_CONNECTION; ++i) {
        if (server->connection[i]) {
            vpftp_connection_free(server->connection[i]);
            server->connection[i] = NULL;
        }
    }
    
    if (server->socket) {
        vpftp_socket_close(server->socket);
    }
    
    if (server->thread) {
        vpftp_thread_join(server->thread);
    }
    
    if (server->access) {
        vpftp_access_free(server->access);
    }
    
    if (server->home) {
        vpftp_free(server->home);
    }
    
    vpftp_free(server);
}

int vpftp_server_listen(vpftp_server_ptr server) {
    int socket = socket_listen_port(server->port);
    
    if (socket == -1) {
        return -1;
    }
    
    server->socket = socket;
    server->maxfd = server->socket;
    
    return 0;
}

int vpftp_server_get_connect(vpftp_server_ptr server) {
    FD_ZERO(&server->active_set);
    FD_SET(server->socket, &server->active_set);
    for (int i = 0; i < VPFTP_MAX_CONNECTION; ++i) {
        if (server->connection[i]) {
            FD_SET(server->connection[i]->control_fd, &server->active_set);
        }
    }
    
    int ret = socket_get_connect(server->maxfd, &server->active_set);
    if (ret > 0) {
        if (FD_ISSET(server->socket, &server->active_set)) {
            server->accept_connect = 1;
        }
        
        for (int i = 0; i < VPFTP_MAX_CONNECTION; ++i) {
            if (server->connection[i] && FD_ISSET(server->connection[i]->control_fd, &server->active_set)) {
                server->connection[i]->received = 1;
            }
        }
    }
    
    return ret;
}

int vpftp_server_accept(vpftp_server_ptr server) {
    int fd = socket_accept_connect(server->socket);
    if (fd < 0) {
        return -1;
    }
    
    for (int i = 0; i < VPFTP_MAX_CONNECTION; ++i) {
        if (!server->connection[i]) {
            server->connection[i] = (vpftp_connection_ptr)vpftp_malloc(sizeof(vpftp_connection));
            vpftp_connection_init(server->connection[i]);
            
            server->connection[i]->control_fd = fd;
            
            if (server->maxfd < fd) {
                server->maxfd = fd;
            }
            
            server->accept_connect = 0;
            
            break;
        }
    }
    
    return fd;
}
