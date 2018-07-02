//
//  server.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/21.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef server_h
#define server_h

#include <sys/unistd.h>
#include "access.h"
#include "connection.h"

#define VPFTP_MAX_CONNECTION 5

struct vpftp_server {
    int socket;
    int port;
    vpftp_connection_ptr connection[VPFTP_MAX_CONNECTION];
    
    int accept_connect;
    int maxfd;
    
    pthread_t thread;
    fd_set active_set;
    
    struct vptfp_access *access;
    char *home;
};

typedef struct vpftp_server vpftp_server;
typedef vpftp_server* vpftp_server_ptr;

void vpftp_server_init(vpftp_server_ptr server, int port, const char *path);
void vpftp_server_free(vpftp_server_ptr);
int vpftp_server_listen(vpftp_server_ptr server);

int vpftp_server_get_connect(vpftp_server_ptr server);
int vpftp_server_accept(vpftp_server_ptr server);


#endif /* server_h */
