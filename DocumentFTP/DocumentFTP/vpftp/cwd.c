//
//  cwd.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "cwd.h"
#include "connection.h"
#include "string.h"
#include "sysapi.h"

void vpftp_command_cwd(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    if (!connection->is_logined) {
        vpftp_connection_send_result(connection->control_fd, 530, "Not logged in.");
    }
    
    char *dir;
    if (arg[0] == '/') {
        dir = vpftp_string_copy(arg);
    } else {
        dir = vpftp_string_format("%s%s/", connection->working_directory, arg);
    }
    
    char *path = vpftp_string_format("%s%s", server->home, connection->working_directory);
    if (vpftp_sys_is_dir(path)) {
        char *pre = connection->working_directory;
        connection->working_directory = dir;
        vpftp_free(pre);
        
        vpftp_connection_send_result(connection->control_fd, 250, "Change directory okay, completed.");
    } else {
        vpftp_connection_send_result(connection->control_fd, 550, "File not found.");
    }
    
    vpftp_free(path);
    
    
}
