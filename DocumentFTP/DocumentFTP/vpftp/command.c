//
//  command.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/22.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "command.h"
#include <string.h>
#include "sysapi.h"
#include "string.h"
#include "log.h"
struct vsftp_command_func {
    char *name;
    void (*func)(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg);
};


static struct vsftp_command_func vsftp_cmd_func_array[] = {
    {"USER", vpftp_command_user},
    {"PASS", vpftp_command_pass},
//    "acct.h"
    {"CWD", vpftp_command_cwd},
//    "cdup.h"
//    "smnt.h"
    {"QUIT", vpftp_command_quit},
//    "rein.h"
    {"PORT", vpftp_command_port},
    {"PASV", vpftp_command_pasv},
    {"TYPE", vpftp_command_type},
//    "stru.h"
//    "mode.h"
    {"RETR", vpftp_command_retr},
//    "stor.h"
//    "stou.h"
//    "appe.h"
//    "allo.h"
//    "rest.h"
//    "rnfr.h"
//    "rnto.h"
//    "abor.h"
//    "dele.h"
//    "rmd.h"
//    "mkd.h"
    {"PWD", vpftp_command_pwd},
    {"LIST", vpftp_command_list},
//    "nlst.h"
//    "site.h"
    {"SYST", vpftp_command_syst}
//    "stat.h"
//    "help.h"
//    "noop.h"
};

void vpftp_command_get(vpftp_command_ptr *cmd_ptr, const char *line) {
    vpftp_command_ptr cmd = (vpftp_command_ptr)vpftp_malloc(sizeof(vpftp_command));
    char* split = strchr(line, ' ');
    
    if (split) {
        size_t len = split - line;
        cmd->cmd = vpftp_malloc(len + 1);
        strncpy(cmd->cmd, line, len);
        cmd->cmd[len] = '\0';
        
        len = strlen(line) - 2 - len - 1;
        cmd->arg = vpftp_malloc(len + 1);
        strncpy(cmd->arg, split + 1, len);
        cmd->arg[len] = '\0';
    } else {
        size_t len = strlen(line) - 2;
        cmd->cmd = vpftp_malloc(len + 1);
        strncpy(cmd->cmd, line, len);
        cmd->cmd[len] = '\0';
        
        cmd->arg = NULL;
    }
    
    *cmd_ptr = cmd;
}

void vpftp_command_free(vpftp_command_ptr cmd) {
    if (cmd->cmd) {
        vpftp_free(cmd->cmd);
    }
    
    if (cmd->arg) {
        vpftp_free(cmd->arg);
    }
    
    vpftp_free(cmd);
}

void vpftp_command_dispatch(vpftp_server_ptr server, vpftp_connection_ptr connection, vpftp_command_ptr cmd) {
    int size = sizeof(vsftp_cmd_func_array) / sizeof(struct vsftp_command_func);
    
    int i;
    for (i = 0; i < size; ++i) {
        struct vsftp_command_func* func = &vsftp_cmd_func_array[i];
        if (vpftp_string_equal(func->name, cmd->cmd)) {
            func->func(server, connection, cmd->arg);
            break;
        }
    }
    
    if (i == size) {
        vpftp_connection_send_result(connection->control_fd, 502, "Command not implemented.");
    }
}


