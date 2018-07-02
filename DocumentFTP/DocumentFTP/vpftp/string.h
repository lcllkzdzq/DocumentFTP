//
//  string.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/25.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef string_h
#define string_h

int vpftp_string_length(const char *str);
int vpftp_string_equal(const char *str1, const char *str2);

char* vpftp_string_copy(const char *str);
char* vpftp_string_format(const char *str, ...);
char* vpftp_string_replace(const char *str, char c, char r);
char* vpftp_string_concat(const char *str1, const char *str2);

#endif /* string_h */
