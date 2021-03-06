//
//  RZAssert.m
//  RZAssert
//
//  Created by Zev Eisenberg on 2/20/15.
//  Copyright (c) 2014 Raizlabs. All rights reserved.
//  http://raizlabs.com/
//
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files (the
//  "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so, subject to
//  the following conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#import "RZAssert.h"

@interface RZAssert ()

@property (copy, nonatomic) void (^loggingHandler)(NSString *message);

@end

@implementation RZAssert

+ (instancetype)sharedInstance
{
    static RZAssert *s_sharedInstance = nil;

    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s_sharedInstance = [[self alloc] init];
    });

    return s_sharedInstance;
}

#pragma mark - Public

+ (void)configureWithLoggingHandler:(void(^)(NSString *message))loggingHandler
{
    if ( !loggingHandler ) {
        // using NSAssert here would be too meta
        [NSException raise:NSInvalidArgumentException format:@"%s: loggingHandler must not be nil. If you want to remove the logging handler, use +removeLoggingHandler instead.", __PRETTY_FUNCTION__];
    }

    [[self sharedInstance] setLoggingHandler:loggingHandler];
}

+ (void)removeLoggingHandler
{
    [[self sharedInstance] setLoggingHandler:nil];
}

+ (void)logMessage:(NSString *)message
{
    if ( !message ) {
        // Using NSAssert here would be too meta (and would not assert if assertions are disabled).
        [NSException raise:NSInvalidArgumentException format:@"%s: message must not be nil", __PRETTY_FUNCTION__];
    }

    void(^loggingHandler)(NSString *) = [[self sharedInstance] loggingHandler];
    
    if ( loggingHandler ) {
        loggingHandler(message);
    }
}

+ (BOOL)hasLogger
{
    return ([[self sharedInstance] loggingHandler] != nil);
}

@end
