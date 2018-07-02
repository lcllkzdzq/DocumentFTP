//
//  connection.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/21.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "connection.h"
#include "sysapi.h"
#include <stdio.h>
#include "string.h"
#include "log.h"

void vpftp_connection_init(struct vpftp_connection* connection) {
    connection->control_fd = 0;
    connection->data_fd = 0;
    connection->data_port = 0;
    connection->is_logined = 0;
    connection->received = 0;
    connection->user = NULL;
    connection->working_directory = vpftp_string_copy("/");
}

void vpftp_connection_free(vpftp_connection_ptr connection) {
    
    if (connection->control_fd) {
        vpftp_socket_close(connection->control_fd);
    }
    
    if (connection->data_fd) {
        vpftp_socket_close(connection->data_fd);
    }
    
    if (connection->data_fd) {
        vpftp_socket_close(connection->data_socket);
    }
    
    if (connection->user) {
        vpftp_free(connection->user);
    }
    
    vpftp_free(connection->working_directory);
    
    vpftp_free(connection);
}

char* vpftp_connection_get_line(struct vpftp_connection* connection) {
    char *line = socket_recv_line(connection->control_fd);
    
    if (line) {
        vpftp_log(INFO, "FD-%d: %s", connection->control_fd, line);
    }
    
    return line;
}

void vpftp_connection_send_result(int fd, int status, const char* result) {
    int length = snprintf(NULL, 0, "%d %s\r\n", status, result) + 1;
    char *buf = (char *)vpftp_malloc(length);
    
    sprintf(buf, "%d %s\r\n", status, result);
    buf[length] = '\0';
    
    socket_send_line(fd, buf);
    
    vpftp_log(INFO, "FD-%d: %s", fd, buf);
    
    vpftp_free(buf);
}
