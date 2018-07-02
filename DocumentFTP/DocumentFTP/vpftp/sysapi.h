//
//  sysapi.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/11.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef sysapi_h
#define sysapi_h

#include "connection.h"
#include <sys/socket.h>

#define MAX_CONNECT 5

typedef unsigned char*  bin_ptr;



char* device_get_ip(void);

int os_file_get(const char *path, bin_ptr* ptr);

int socket_listen_port(int port);
int socket_get_connect(int maxfd, fd_set* active_set);
int socket_accept_connect(int socket);


void socket_send_bin(int fd, unsigned char *bin, int len);
void socket_send_line(int fd, const char* line);

int socket_get_port(int socket);
char* socket_recv_line(int fd);




void* vpftp_malloc(size_t size);
void* vpftp_realloc(void *p, size_t size);
void vpftp_free(void *p);

char* vpftp_sys_get_ls(const char *path);
int vpftp_sys_is_dir(const char *path);

int vpftp_thread_create(pthread_t *thread, void *func, void *arg);
int vpftp_thread_join(pthread_t thread);

int vpftp_socket_send_file(int socket, const char *path);
void vpftp_socket_close(int fd);
#endif /* sysapi_h */
