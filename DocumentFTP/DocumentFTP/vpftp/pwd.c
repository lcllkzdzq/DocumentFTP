//
//  pwd.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "pwd.h"
#include "connection.h"
#include "string.h"
#include "sysapi.h"

void vpftp_command_pwd(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg) {
    char *dir = vpftp_string_format("\"%s\" is current directory.", connection->working_directory);
    vpftp_connection_send_result(connection->control_fd, 257, dir);
    
    vpftp_free(dir);
}
