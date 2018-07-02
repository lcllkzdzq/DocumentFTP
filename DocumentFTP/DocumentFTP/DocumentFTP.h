//
//  DocumentFTP.h
//  DocumentFTP
//
//  Created by lcl李成龙 on 2018/6/7.
//  Copyright © 2018 lcl李成龙. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DocumentFTP : NSObject

@property (nonatomic) NSInteger port;
@property (nonatomic) BOOL allowAnonymous;
@property (nonatomic, copy) NSArray *access;

- (void)start;
- (void)stop;

@end
