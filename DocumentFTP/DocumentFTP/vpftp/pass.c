//
//  pass.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/15.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "pass.h"
#include "string.h"


void vpftp_command_pass(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    struct vptfp_access *access = server->access;
    
    if (connection->user > 0) {
        if (vpftp_access_can_access(access, connection->user, arg)) {
            connection->is_logined = 1;
            vpftp_connection_send_result(connection->control_fd, 230, "User logged in, proceed.");
        } else {
            vpftp_connection_send_result(connection->control_fd, 530, "Password error.");
        }        
    } else {
        vpftp_connection_send_result(connection->control_fd, 530, "Password error.");
    }
}
