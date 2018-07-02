//
//  list.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef list_h
#define list_h

#include "server.h"

void vpftp_command_list(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg);

#endif /* list_h */
