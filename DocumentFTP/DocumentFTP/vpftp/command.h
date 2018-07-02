//
//  command.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/22.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef command_h
#define command_h

#include "user.h"
#include "pass.h"
#include "acct.h"
#include "cwd.h"
#include "cdup.h"
#include "smnt.h"
#include "quit.h"
#include "rein.h"
#include "port.h"
#include "pasv.h"
#include "type.h"
#include "stru.h"
#include "mode.h"
#include "retr.h"
#include "stor.h"
#include "stou.h"
#include "appe.h"
#include "allo.h"
#include "rest.h"
#include "rnfr.h"
#include "rnto.h"
#include "abor.h"
#include "dele.h"
#include "rmd.h"
#include "mkd.h"
#include "pwd.h"
#include "list.h"
#include "nlst.h"
#include "site.h"
#include "syst.h"
#include "stat.h"
#include "help.h"
#include "noop.h"


struct vpftp_command {
    char *cmd;
    char *arg;
};

typedef struct vpftp_command vpftp_command;
typedef vpftp_command* vpftp_command_ptr;

void vpftp_command_get(vpftp_command_ptr *cmd_ptr, const char *line);
void vpftp_command_free(vpftp_command_ptr cmd);
void vpftp_command_dispatch(vpftp_server_ptr server, vpftp_connection_ptr connection, vpftp_command_ptr cmd);


#endif /* command_h */
