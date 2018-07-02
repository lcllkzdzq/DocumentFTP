//
//  string.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/25.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "string.h"
#include <string.h>
#include "sysapi.h"
#include <stdarg.h>
#include <stdio.h>

int vpftp_string_length(const char *str) {
    return (int)strlen(str);
}

int vpftp_string_equal(const char *str1, const char *str2) {
    return strcmp(str1, str2) == 0;
}

char* vpftp_string_copy(const char *str) {
    char *ret = (char *)vpftp_malloc(strlen(str) + 1);
    strcpy(ret, str);
    
    return ret;
}



char* vpftp_string_format(const char *str, ...) {
    va_list ap;
    
    va_start(ap, str);
    int len = vsnprintf(NULL, 0, str, ap);
    va_end(ap);
    
    char *buf = (char *)vpftp_malloc(len + 1);
    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);
    
    return buf;
}

char* vpftp_string_replace(const char *str, char c, char r) {
    char *ret = (char *)vpftp_malloc(strlen(str) + 1);
    strcpy(ret, str);
    
    char *p;
    while ((p = strchr(ret, c))) {
        *p = r;
    }
    
    return ret;
}

char* vpftp_string_concat(const char *str1, const char *str2) {
    char *ret = (char *)vpftp_malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(ret, str1);
    strcat(ret, str2);
    
    return ret;
}
