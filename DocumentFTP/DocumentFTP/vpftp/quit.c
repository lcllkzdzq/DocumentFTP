//
//  quit.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "quit.h"
#include "sysapi.h"

void vpftp_command_quit(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    vpftp_connection_send_result(connection->control_fd, 221, "Service closing control connection.");
    
    for (int i = 0; i < MAX_CONNECT; ++i) {
        if (server->connection[i] == connection) {
            vpftp_connection_free(connection);
            server->connection[i] = NULL;
        }
    }
}
