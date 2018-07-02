//
//  DocumentFTP.m
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/7.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#import "DocumentFTP.h"
#import "vpftp/vpftp.h"

@implementation DocumentFTP {
    vpftp_server* _server;
}

- (void)start {
    NSString *documentDir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    
    vpftp_start(&_server, (int)_port, [documentDir UTF8String]);
    
    if (_server) {
        vpftp_allow_anonymous(_server, _allowAnonymous);
        
        for (NSDictionary *dic in _access) {
            NSString *username = dic[@"UserName"];
            NSString *password = dic[@"Password"];
            
            vpftp_add_access(_server, [username UTF8String], [password UTF8String]);
        }
    }
}

- (void)stop {
    if (_server) {
        vpftp_stop(_server);
    }
}

@end
