//
//  sysapi.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/11.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "sysapi.h"


#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "string.h"
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

#define MAX_CLIENT 5
#define MAX_BUFFER 100

void* vpftp_malloc(size_t size) {
    return malloc(size);
}

void* vpftp_realloc(void *p, size_t size) {
    return p ? realloc(p, size) : vpftp_malloc(size);
}

void vpftp_free(void *p) {
    return free(p);
}




char* device_get_ip() {
    struct ifaddrs *addr;
    struct ifaddrs *cur;
    char *ipaddr = NULL;
    
    int success = getifaddrs(&addr);
    if (success == 0) {
        cur = addr;
        
        while (cur != NULL) {
            if( cur->ifa_addr->sa_family == AF_INET) {
                if (vpftp_string_equal(cur->ifa_name, "en0")) {
                    ipaddr = inet_ntoa(((struct sockaddr_in *)cur->ifa_addr)->sin_addr);
                    break;
                }
            }
            
            cur = cur->ifa_next;
        }
    }
    
    freeifaddrs(addr);
    
    return ipaddr;
}

int socket_listen_port(int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == -1) {
        return -1;
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sockfd);
        return -1;
    }
    
    if (listen(sockfd, MAX_CLIENT) < 0) {
        close(sockfd);
        return -1;
    }
    
    return sockfd;
}


int socket_get_connect(int maxfd, fd_set* active_set) {
    return select(maxfd + 1, active_set, NULL, NULL, NULL);
}

int socket_accept_connect(int socket) {
    return accept(socket, NULL, NULL);
}

void socket_send_line(int fd, const char* line) {
    send(fd, line, strlen(line), 0);
}

void socket_send_bin(int fd, unsigned char *bin, int len) {
    send(fd, bin, len, 0);
}



char* socket_recv_line(int fd) {
    char* buf = vpftp_malloc(MAX_BUFFER);
    size_t buf_len = MAX_BUFFER;
    char* p = buf;
    size_t len = 0;
    
    do {
        size_t size = recv(fd, p, buf_len - (p - buf), 0);
        if ((int)size <= 0) {
            break;
        }
        
        p += size;
        len = p - buf;
        
        buf_len += MAX_BUFFER;
        buf = vpftp_realloc(buf, buf_len);
        p = buf + len;
    } while (buf[len-1] != '\n' || buf[len-2] != '\r');
    
    if (len != 0) {
        buf = vpftp_realloc(buf, len + 1);
        buf[len] = '\0';
    } else {
        vpftp_free(buf);
        buf = NULL;
    }
    
    return buf;
}

int socket_get_port(int socket) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    
    if (getsockname(socket, (struct sockaddr *)&addr, &len) < 0) {
        return -1;
    }
    
    return addr.sin_port;
}


int os_file_get(const char *path, bin_ptr* ptr) {
    int fd = open(path, O_RDONLY);
    if (fd == 0) {
        return -1;
    }
    
    bin_ptr buf = (bin_ptr)vpftp_malloc(MAX_BUFFER);
    size_t buf_len = MAX_BUFFER;
    bin_ptr p = buf;
    ssize_t len = 0;
    
    ssize_t size;
    while ((size = read(fd, p, buf_len - (p - buf)))) {
        p += size;
        len = p - buf;
        
        buf_len += MAX_BUFFER;
        buf = vpftp_realloc(buf, buf_len);
        p = buf + len;
    }
    
    *ptr = buf;
    
    return (int)len;
}

// file
static void mode_to_str(mode_t mode, char str[11]) {
    strcpy(str, "----------");
    
    if (S_ISDIR(mode)) str[0] = 'd';
    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}



char* vpftp_sys_get_ls(const char *path) {
    DIR *dirp = opendir(path);
    if (!dirp) {
        return NULL;
    }
    
    char *content = vpftp_string_copy("");
    
    struct dirent *dp;
    while((dp = readdir(dirp))){
        if(vpftp_string_equal(dp->d_name, ".") || vpftp_string_equal(dp->d_name, "..")){
            continue;
        }

        char *fp = vpftp_string_format("%s/%s", path, dp->d_name);
        struct stat st;
        stat(fp, &st);
        vpftp_free(fp);

        char mode[11];
        mode_to_str(st.st_mode, mode);
        
        off_t size = st.st_size;
        char *date = ctime(&st.st_mtime);
        char *name = dp->d_name;
        
        char *pre = content;
        char *str = vpftp_string_format("%s   1 owner    group %15ld %.12s %s\r\n", mode, size, date + 4, name);
        content = vpftp_string_concat(pre, str);
        
        vpftp_free(pre);
        vpftp_free(str);
    }
    
    closedir(dirp);
    
    return content;
}

int vpftp_sys_is_dir(const char *path) {
    struct stat st;
    stat(path, &st);
    
    return S_ISDIR(st.st_mode);
}

int vpftp_socket_send_file(int socket, const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd == 0) {
        return -1;
    }
    
    char buf[MAX_BUFFER];
    
    ssize_t size;
    while ((size = read(fd, buf, MAX_BUFFER))) {
        send(socket, buf, size, 0);
    }
    
    close(fd);

    return 0;
}

int vpftp_thread_create(pthread_t *thread, void *func, void *arg) {
    if (pthread_create(thread, NULL, func, arg)) {
        return -1;
    }
    
    return 0;
}

int vpftp_thread_join(pthread_t thread) {
    if (pthread_join(thread, NULL)) {
        return -1;
    }
    
    return 0;
}


void vpftp_socket_close(int fd) {
    int ret = close(fd);

    vpftp_log(INFO, "FD-%d: close - result: %d", fd, ret);
}
