//
//  syst.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/19.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef syst_h
#define syst_h

#include "server.h"

void vpftp_command_syst(struct vpftp_server* server, struct vpftp_connection* connection, const char* arg);

#endif /* syst_h */
