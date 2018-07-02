//
//  log.h
//  DocumentFTP
//
//  Created by lcl on 2018/6/30.
//  Copyright © 2018年 lcl李成龙. All rights reserved.
//

#ifndef log_h
#define log_h

enum {
    INFO,
    WARNING,
    ERROR,
    UNKNOW
};

void vpftp_log(int level, const char* str, ...);

#endif /* log_h */
