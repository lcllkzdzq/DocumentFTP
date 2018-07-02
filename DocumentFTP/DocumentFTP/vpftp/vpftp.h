//
//  vpftp.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/20.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef vpftp_h
#define vpftp_h

#include "server.h"

int vpftp_start(vpftp_server_ptr* server_t, int port, const char *path);
void vpftp_stop(vpftp_server_ptr server);

void vpftp_allow_anonymous(vpftp_server_ptr server, int allow_anonymous);
void vpftp_add_access(vpftp_server_ptr server, const char* username, const char* password);

#endif /* vpftp_h */
