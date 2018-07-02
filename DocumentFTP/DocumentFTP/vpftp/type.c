//
//  type.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "type.h"
#include "connection.h"
#include "string.h"
#include "sysapi.h"

void vpftp_command_type(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    if (connection->is_logined) {
        char *str = vpftp_string_format("TYPE %s accept.", arg);
        vpftp_connection_send_result(connection->control_fd, 200, str);
        vpftp_free(str);
    } else {
        vpftp_connection_send_result(connection->control_fd, 530, "Not logged in.");
    }
}
