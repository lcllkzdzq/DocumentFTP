//
//  list.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "list.h"
#include "sysapi.h"
#include "string.h"

void vpftp_command_list(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    vpftp_connection_send_result(connection->control_fd, 125, "Data connection already open; Transfer starting.");

    char *path = vpftp_string_concat(server->home, connection->working_directory);
    char *content = vpftp_sys_get_ls(path);
    
    socket_send_line(connection->data_fd, content);
    
    vpftp_socket_close(connection->data_fd);
    vpftp_socket_close(connection->data_socket);
    connection->data_fd = 0;
    connection->data_socket = 0;
    
    vpftp_free(path);
    vpftp_free(content);
    
    vpftp_connection_send_result(connection->control_fd, 226, "Transfer complete.");
}
