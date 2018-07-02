//
//  user.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/14.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef user_h
#define user_h

#include "server.h"

void vpftp_command_user(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg);

#endif /* user_h */
