//
//  pasv.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "pasv.h"
#include "sysapi.h"
#include "string.h"

void vpftp_command_pasv(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    
    if (!connection->is_logined) {
        vpftp_connection_send_result(connection->control_fd, 530, "Not logged in.");
    }
    
    connection->data_socket = socket_listen_port(0);
    connection->data_port = ntohs(socket_get_port(connection->data_socket));

    char *ipaddr = vpftp_string_replace(device_get_ip(), '.', ',');
    char *desc = vpftp_string_format("Entering Passive Mode (%s,%d,%d).", ipaddr, connection->data_port >> 8, connection->data_port & 255);
    vpftp_connection_send_result(connection->control_fd, 227, desc);
    
    vpftp_free(ipaddr);
    vpftp_free(desc);
    
    connection->data_fd = accept(connection->data_socket, NULL, NULL);
}
