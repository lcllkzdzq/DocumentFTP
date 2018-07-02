//
//  pass.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/15.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef pass_h
#define pass_h

#include "connection.h"
#include "server.h"

void vpftp_command_pass(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg);

#endif /* pass_h */
