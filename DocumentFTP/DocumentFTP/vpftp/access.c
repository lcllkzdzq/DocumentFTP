//
//  access.c
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/25.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#include "access.h"
#include "sysapi.h"
#include "string.h"

void vpftp_access_init(vptfp_access_ptr access) {
    access->users = NULL;
    access->allow_anonymous = 0;
    access->user_count = 0;
}

void vpftp_access_free(vptfp_access_ptr access) {
    if (access->user_count > 0) {
        for (int i = 0; i < access->user_count; ++i) {
            vptfp_user_ptr user = access->users[i];
            vpftp_free(user->username);
            vpftp_free(user->password);
            vpftp_free(user);
        }
    }
    
    vpftp_free(access);
}

void vpftp_access_add_user(vptfp_access_ptr access, const char* username, const char* password) {
    vptfp_user_ptr user = (vptfp_user_ptr)vpftp_malloc(sizeof(vptfp_user));
    user->username = vpftp_string_copy(username);
    user->password = vpftp_string_copy(password);
    
    access->user_count++;

    access->users = (vptfp_user_ptr *)vpftp_realloc(access->users, sizeof(vptfp_user_ptr) * access->user_count);
    access->users[access->user_count - 1] = user;
}

int vpftp_access_is_anonymous(vptfp_access_ptr access, const char* username) {
    if (access->allow_anonymous && vpftp_string_equal(username, "anonymous")) {
        return 1;
    }
    
    return 0;
}

int vpftp_access_is_user(vptfp_access_ptr access, const char* username) {
    for (int i = 0; i < access->user_count; ++i) {
        if (vpftp_string_equal(username, access->users[i]->username)) {
            return 1;
        }
    }
    
    return 0;
}

int vpftp_access_can_access(vptfp_access_ptr access, const char* username, const char* password) {
    for (int i = 0; i < access->user_count; ++i) {
        if (vpftp_string_equal(username, access->users[i]->username) && vpftp_string_equal(password, access->users[i]->password) ) {
            return 1;
        }
    }
    
    return 0;
}
