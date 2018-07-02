//
//  vpftp.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/20.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "vpftp.h"
#include "sysapi.h"
#include "command.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "server.h"
#include "string.h"

#include "log.h"

static void loopFunc(vpftp_server_ptr server) {
    while (1) {
        // select
        int ret = vpftp_server_get_connect(server);
        if (ret < 0) {        // select error
            break;
        }

        // accept
        if (server->accept_connect) {
            int fd = vpftp_server_accept(server);
            if (fd < 0) {                               // accept error
                break;
            }

            vpftp_connection_send_result(fd, 200, "ok");
        }

        for (int i = 0; i < VPFTP_MAX_CONNECTION; ++i) {
            if (server->connection[i] && server->connection[i]->received) {
                char* line = vpftp_connection_get_line(server->connection[i]);
                if (!line) {                                    // connect close
                    vpftp_connection_free(server->connection[i]);
                    server->connection[i] = NULL;
                    continue;
                }

                vpftp_command_ptr cmd;

                vpftp_command_get(&cmd, line);
                vpftp_command_dispatch(server, server->connection[i], cmd);

                vpftp_command_free(cmd);

                vpftp_free(line);

                server->connection[i]->received = 0;
            }
        }
    }
}

int vpftp_start(vpftp_server_ptr* server_t, int port, const char *path) {
    vpftp_server_ptr server = (vpftp_server_ptr)vpftp_malloc(sizeof(vpftp_server));
    vpftp_server_init(server, port, path);

    if (vpftp_server_listen(server) < 0) {
        vpftp_server_free(server);
        vpftp_log(ERROR, "socket listen error");
        
        *server_t = NULL;
        return 0;
    }
    
    if (vpftp_thread_create(&server->thread, &loopFunc, server) < 0) {
        vpftp_server_free(server);
        vpftp_log(ERROR, "thread create error");
        
        *server_t = NULL;
        return 0;
    };
    
    *server_t = server;
    return 1;
}

void vpftp_stop(vpftp_server_ptr server) {
    vpftp_server_free(server);
}

void vpftp_allow_anonymous(vpftp_server_ptr server, int allow_anonymous) {
    server->access->allow_anonymous = allow_anonymous;
}

void vpftp_add_access(vpftp_server_ptr server, const char* username, const char* password) {
    vpftp_access_add_user(server->access, username, password);
}
