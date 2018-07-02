//
//  user.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/14.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "user.h"
#include "connection.h"
#include "string.h"
#include "access.h"

void vpftp_command_user(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    struct vptfp_access *access = server->access;
    
    if (arg) {
        if (vpftp_access_is_anonymous(access, arg)) {
            connection->user = vpftp_string_copy(arg);
            connection->is_logined = 1;
            vpftp_connection_send_result(connection->control_fd, 230, "User logged in, proceed.");
        } else if (vpftp_access_is_user(access, arg)) {
            connection->user = vpftp_string_copy(arg);
            vpftp_connection_send_result(connection->control_fd, 331, "User name okay, need password.");
        } else {
            vpftp_connection_send_result(connection->control_fd, 530, "User not exist.");
        }
    } else {
        vpftp_connection_send_result(connection->control_fd, 530, "User not exist.");
    }
}
