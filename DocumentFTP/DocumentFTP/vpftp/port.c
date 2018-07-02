//
//  port.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "port.h"
#include "connection.h"

void vpftp_command_port(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    vpftp_connection_send_result(connection->control_fd, 502, "Command not implemented.");
}
