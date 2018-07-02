//
//  connection.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/21.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef connection_h
#define connection_h

struct vpftp_connection {
    int control_fd;
    int data_fd;
    
    int data_socket;
    int data_port;
    
    int is_logined;
    char* user;
    
    char* working_directory;
    
    int received;
};

typedef struct vpftp_connection vpftp_connection;
typedef vpftp_connection* vpftp_connection_ptr;

void vpftp_connection_init(vpftp_connection_ptr connection);
void vpftp_connection_free(vpftp_connection_ptr connection);

char* vpftp_connection_get_line(struct vpftp_connection* connection);
void vpftp_connection_send_result(int fd, int status, const char* result);

#endif /* connection_h */
