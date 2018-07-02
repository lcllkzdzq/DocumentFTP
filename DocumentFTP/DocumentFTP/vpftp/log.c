//
//  log.c
//  DocumentFTP
//
//  Created by lcl on 2018/6/30.
//  Copyright © 2018年 lcl李成龙. All rights reserved.
//

#include "log.h"
#include "sysapi.h"
#include "string.h"

#include <stdarg.h>
#include <stdio.h>

static const char *get_level_str(int level) {
    switch (level) {
        case INFO:
            return "INFO";
        case WARNING:
            return "WARN";
        case ERROR:
            return "EROR";
        default:
            return "UNKN";
    }
}

void vpftp_log(int level, const char* str, ...) {
    va_list ap;
    
    va_start(ap, str);
    int len = vsnprintf(NULL, 0, str, ap);
    va_end(ap);
    
    char *buf = (char *)vpftp_malloc(len + 1);
    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);
    
    printf("[%s]: %s\n", get_level_str(level), buf);
    
    vpftp_free(buf);
}
