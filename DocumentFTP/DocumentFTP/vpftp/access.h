//
//  access.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/25.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#ifndef access_h
#define access_h

struct vptfp_user {
    char* username;
    char* password;
};

typedef struct vptfp_user vptfp_user;
typedef vptfp_user* vptfp_user_ptr;

struct vptfp_access {
    int user_count;
    vptfp_user_ptr *users;
    int allow_anonymous;
};

typedef struct vptfp_access vptfp_access;
typedef vptfp_access* vptfp_access_ptr;

void vpftp_access_init(vptfp_access_ptr access);
void vpftp_access_free(vptfp_access_ptr access);
void vpftp_access_add_user(vptfp_access_ptr access, const char* username, const char* password);

int vpftp_access_is_anonymous(vptfp_access_ptr access, const char* username);
int vpftp_access_is_user(vptfp_access_ptr access, const char* username);
int vpftp_access_can_access(vptfp_access_ptr access, const char* username, const char* password);


#endif /* access_h */
