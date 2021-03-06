//
//  RZAssertTests.m
//  RZAssertTests
//
//  Created by Raizlabs on 11/24/2014.
//  Copyright (c) 2014 Raizlabs. All rights reserved.
//

#import "RZAssert.h"

static NSString* const kNilString = nil;
static NSString* const kEmptyString = @"";
static NSString* const kNonEmptyString = @"non-empty string";
static NSString* const kTestMessage = @"test message";

typedef void (^AssertionBlock)(void);
typedef void (^LoggingAssertionBlock)(NSString *message);

static BOOL testAssertionWithBlock(AssertionBlock block)
{
    NSCAssert(block != nil, @"assertion block must not be nil");

    __block NSString *loggedMessage = nil;
    [RZAssert configureWithLoggingHandler:^(NSString *message) {
        loggedMessage = message;
    }];

    BOOL assertedOrLogged = NO;

#if defined(NS_BLOCK_ASSERTIONS)
    block();
    if ( loggedMessage ) {
        assertedOrLogged = YES;
    }
#else
    @try {
        block();
    }
    @catch (__unused NSException *e) {
        assertedOrLogged = YES;
    }
#endif

    return assertedOrLogged;
}

static BOOL testLoggingAssertionWithBlock(LoggingAssertionBlock loggingBlock)
{
    NSCAssert(loggingBlock != nil, @"logging block must not be nil");

    __block NSString *loggedMessage = nil;
    [RZAssert configureWithLoggingHandler:^(NSString *message) {
        loggedMessage = message;
    }];

    BOOL assertedOrLogged = NO;

#if defined(NS_BLOCK_ASSERTIONS)
    loggingBlock(kNonEmptyString);
    if ( [loggedMessage containsString:kNonEmptyString] ) {
        assertedOrLogged = YES;
    }
#else
    @try {
        loggingBlock(kNonEmptyString);
    }
    @catch (NSException *e) {
        assertedOrLogged = ([e.description rangeOfString:kNonEmptyString].location != NSNotFound);
    }
#endif

    return assertedOrLogged;
}

SpecBegin(RZAssert)

describe(@"RZASSERT_NIL works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_NIL(kNilString);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_NIL(kNonEmptyString);
        })).to.beTruthy();
    });

});

describe(@"setting a nil logging handler", ^{

    it(@"throws an exception", ^{
        BOOL excepted = NO;

        @try {
            [RZAssert configureWithLoggingHandler:nil];
        }
        @catch (__unused NSException *e) {
            excepted = YES;
        }

        expect(excepted).to.beTruthy();
    });

});

describe(@"+removeLoggingHandler works.", ^{

    it(@"is a no-op when there is no logging handler", ^{
        id testThing = nil;

        [RZAssert removeLoggingHandler];

        // Make sure the assignment that is passed in does not run when there is no logging handler configured.
        // We only care about this case when assertions are disabled.
#if defined(NS_BLOCK_ASSERTIONS)
        RZASSERT_NOT_NIL((testThing = kNonEmptyString));
#endif
        expect(testThing).to.beNil();

    });

});

describe(@"RZCASSERT_NIL works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_NIL(kNilString);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_NIL(kNonEmptyString);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_NOT_NIL works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_NOT_NIL(nil);
        })).to.beTruthy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_NOT_NIL(kNonEmptyString);
        })).to.beFalsy();
    });
});

describe(@"RZCASSERT_NOT_NIL works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_NOT_NIL(nil);
        })).to.beTruthy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_NOT_NIL(kNonEmptyString);
        })).to.beFalsy();
    });
});

describe(@"RZASSERT_ALWAYS works", ^{

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_ALWAYS;
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_ALWAYS works", ^{

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_ALWAYS;
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_TRUE works", ^{

    it(@"handles non-nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE(!kNilString);
        })).to.beFalsy();
    });

    it(@"handles nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE(kNilString);
        })).to.beTruthy();
    });

    it(@"handles NO correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE(NO);
        })).to.beTruthy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE(YES);
        })).to.beFalsy();
    });

});

describe(@"RZCASSERT_TRUE works", ^{

    it(@"handles non-nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE(!kNilString);
        })).to.beFalsy();
    });

    it(@"handles nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE(kNilString);
        })).to.beTruthy();
    });

    it(@"handles NO correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE(NO);
        })).to.beTruthy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE(YES);
        })).to.beFalsy();
    });

});

describe(@"RZASSERT_FALSE works", ^{

    it(@"handles nil correctly", ^{
        RZASSERT_FALSE(kNilString);
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_FALSE(!kNilString);
        })).to.beTruthy();
    });

    it(@"handles NO correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_FALSE(NO);
        })).to.beFalsy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_FALSE(YES);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_FALSE works", ^{

    it(@"handles nil correctly", ^{
        RZCASSERT_FALSE(kNilString);
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_FALSE(!kNilString);
        })).to.beTruthy();
    });

    it(@"handles NO correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_FALSE(NO);
        })).to.beFalsy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_FALSE(YES);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_WITH_MESSAGE works", ^{

    it(@"prints message on assert", ^{

        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_WITH_MESSAGE(@"%@", message);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_WITH_MESSAGE works", ^{

    it(@"prints message on assert", ^{

        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_WITH_MESSAGE(@"%@", message);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_WITH_MESSAGE_LOG works", ^{

    it(@"prints a message on assert", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_WITH_MESSAGE_LOG(kNonEmptyString, @"%@", message);
        })).to.beTruthy();
    });
});

describe(@"RZCASSERT_WITH_MESSAGE_LOG works", ^{

    it(@"prints a message on assert", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_WITH_MESSAGE_LOG(kNonEmptyString, @"%@", message);
        })).to.beTruthy();
    });
});

describe(@"RZASSERT_TRUE_WITH_MESSAGE works", ^{

    it(@"handles nil correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_TRUE_WITH_MESSAGE(kNilString, @"%@", message);
        })).to.beTruthy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE_WITH_MESSAGE(YES, @"%@", kTestMessage);
        })).to.beFalsy();
    });

    it(@"handles NO correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_TRUE_WITH_MESSAGE(NO, @"%@", message);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_TRUE_WITH_MESSAGE works", ^{

    it(@"handles nil correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_TRUE_WITH_MESSAGE(kNilString, @"%@", message);
        })).to.beTruthy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE_WITH_MESSAGE(YES, @"%@", kTestMessage);
        })).to.beFalsy();
    });

    it(@"handles NO correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_TRUE_WITH_MESSAGE(NO, @"%@", message);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_TRUE_WITH_MESSAGE_LOG works", ^{

    it(@"handles nil correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_TRUE_WITH_MESSAGE_LOG(nil, kNonEmptyString, @"%@", message);
        })).to.beTruthy();
    });

    it(@"handles NO correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_TRUE_WITH_MESSAGE_LOG(NO, kNonEmptyString, @"%@", message);
        })).to.beTruthy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE_WITH_MESSAGE_LOG(YES, kNonEmptyString, @"%@", kTestMessage);
        })).to.beFalsy();
    });

});

describe(@"RZCASSERT_TRUE_WITH_MESSAGE_LOG works", ^{

    it(@"handles nil correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_TRUE_WITH_MESSAGE_LOG(nil, kNonEmptyString, @"%@", message);
        })).to.beTruthy();
    });

    it(@"handles NO correctly", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_TRUE_WITH_MESSAGE_LOG(NO, kNonEmptyString, @"%@", message);
        })).to.beTruthy();
    });

    it(@"handles YES correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE_WITH_MESSAGE_LOG(YES, kNonEmptyString, @"%@", kTestMessage);
        })).to.beFalsy();
    });

});

describe(@"RZASSERT_TRUE_LOG works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE_LOG(kNilString, kNonEmptyString);
        }));
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_TRUE_LOG(kNonEmptyString, kTestMessage);
        })).to.beFalsy();
    });

    it(@"logs a message", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZASSERT_TRUE_LOG(NO, message);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_TRUE_LOG works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE_LOG(kNilString, kNonEmptyString);
        }));
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_TRUE_LOG(kNonEmptyString, kTestMessage);
        })).to.beFalsy();
    });

    it(@"logs a message", ^{
        expect(testLoggingAssertionWithBlock(^(NSString *message) {
            RZCASSERT_TRUE_LOG(NO, message);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_EQUAL_OBJECT_POINTERS works", ^{

    it(@"handles nil correcty", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_EQUAL_OBJECT_POINTERS(kNilString, kNilString);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_EQUAL_OBJECT_POINTERS(kTestMessage, kNonEmptyString);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_EQUAL_OBJECT_POINTERS works", ^{

    it(@"handles nil correcty", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_EQUAL_OBJECT_POINTERS(kNilString, kNilString);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_EQUAL_OBJECT_POINTERS(kTestMessage, kNonEmptyString);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_EQUAL_OBJECTS works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_EQUAL_OBJECTS(kNilString, kNilString);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_EQUAL_OBJECTS(kNonEmptyString, kNonEmptyString);
        })).to.beFalsy();
    });

    it(@"handles non-pointer-equal objects correctly", ^{
        expect(testAssertionWithBlock(^{
            NSString *literalString = @"one";
            NSString *composedString = [@"on" stringByAppendingString:@"e"];

            expect(testAssertionWithBlock(^{
                RZASSERT_EQUAL_OBJECTS(literalString, composedString);
            })).to.beFalsy();
        }));
    });

});

describe(@"RZCASSERT_EQUAL_OBJECTS works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_EQUAL_OBJECTS(kNilString, kNilString);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_EQUAL_OBJECTS(kNonEmptyString, kNonEmptyString);
        })).to.beFalsy();
    });

    it(@"handles non-pointer-equal objects correctly", ^{
        expect(testAssertionWithBlock(^{
            NSString *literalString = @"one";
            NSString *composedString = [@"on" stringByAppendingString:@"e"];

            expect(testAssertionWithBlock(^{
                RZCASSERT_EQUAL_OBJECTS(literalString, composedString);
            })).to.beFalsy();
        }));
    });

});

describe(@"RZASSERT_EQUAL_STRINGS works", ^{

    it(@"handles equal strings correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_EQUAL_STRINGS(kNonEmptyString, kNonEmptyString);
        })).to.beFalsy();
    });

    it(@"handles nonequal strings correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_EQUAL_STRINGS(kNonEmptyString, kTestMessage);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_EQUAL_STRINGS works", ^{

    it(@"handles equal strings correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_EQUAL_STRINGS(kNonEmptyString, kNonEmptyString);
        })).to.beFalsy();
    });

    it(@"handles nonequal strings correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_EQUAL_STRINGS(kNonEmptyString, kTestMessage);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_NONEMPTY_STRING works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_NONEMPTY_STRING(kNilString);
        })).to.beTruthy();
    });

    it(@"handles nonempty string correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_NONEMPTY_STRING(kNonEmptyString);
        })).to.beFalsy();
    });

});

describe(@"RZCASSERT_NONEMPTY_STRING works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_NONEMPTY_STRING(kNilString);
        })).to.beTruthy();
    });

    it(@"handles nonempty string correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_NONEMPTY_STRING(kNonEmptyString);
        })).to.beFalsy();
    });

});

describe(@"RZASSERT_KINDOF works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF(kNilString, [NSObject class]);
        })).to.beTruthy();
    });

    it(@"handles classes correctly when you don’t explicitly call +class", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF(kNilString, NSObject);
        })).to.beTruthy();
    });

    it(@"handles non-nil value correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF(kNonEmptyString, [NSString class]);
        })).to.beFalsy();
    });

    it(@"handles non-matching class correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF(kNonEmptyString, [NSNumber class]);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_KINDOF works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF(kNilString, [NSObject class]);
        })).to.beTruthy();
    });

    it(@"handles classes correctly when you don’t explicitly call +class", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF(kNilString, NSObject);
        })).to.beTruthy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF(kNonEmptyString, [NSString class]);
        })).to.beFalsy();
    });

    it(@"handles non-matching class correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF(kNonEmptyString, [NSNumber class]);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_KINDOF_OR_NIL works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF_OR_NIL(kNilString, [NSObject class]);
        })).to.beFalsy();
    });

    it(@"handles classes correctly when you don’t explicitly call +class", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF_OR_NIL(kNilString, NSObject);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF_OR_NIL(kNonEmptyString, [NSString class]);
        })).to.beFalsy();
    });

    it(@"handles non-matching class correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_KINDOF_OR_NIL(kNonEmptyString, [NSNumber class]);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_KINDOF_OR_NIL works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF_OR_NIL(kNilString, [NSObject class]);
        })).to.beFalsy();
    });

    it(@"handles classes correctly when you don’t explicitly call +class", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF_OR_NIL(kNilString, NSObject);
        })).to.beFalsy();
    });

    it(@"handles non-nil values correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF_OR_NIL(kNonEmptyString, [NSString class]);
        })).to.beFalsy();
    });

    it(@"handles non-matching class correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_KINDOF_OR_NIL(kNonEmptyString, [NSNumber class]);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_CONFORMS_PROTOCOL works", ^{

    it(@"handles nil objects correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CONFORMS_PROTOCOL(kNilString, @protocol(NSObject));
        })).to.beTruthy();
    });

    it(@"handles non-conformant objects correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CONFORMS_PROTOCOL(kNonEmptyString, @protocol(NSXMLParserDelegate));
        })).to.beTruthy();
    });

    it(@"handles conformant objects correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CONFORMS_PROTOCOL(kNonEmptyString, @protocol(NSObject));
        })).to.beFalsy();
    });

});

describe(@"RZCASSERT_CONFORMS_PROTOCOL works", ^{

    it(@"handles nil objects correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CONFORMS_PROTOCOL(kNilString, @protocol(NSObject));
        })).to.beTruthy();
    });

    it(@"handles non-conformant objects correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CONFORMS_PROTOCOL(kNonEmptyString, @protocol(NSXMLParserDelegate));
        })).to.beTruthy();
    });

    it(@"handles conformant objects correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CONFORMS_PROTOCOL(kNonEmptyString, @protocol(NSObject));
        })).to.beFalsy();
    });

});

describe(@"RZASSERT_CLASS_SUBCLASS_OF_CLASS works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CLASS_SUBCLASS_OF_CLASS([kNilString class], [NSObject class]);
        })).to.beTruthy();
    });

    it(@"handles classes correctly when you don’t explicitly call +class, or when you pass an object", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CLASS_SUBCLASS_OF_CLASS(kNilString, NSObject);
        })).to.beTruthy();
    });

    it(@"handles non-subclasses correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CLASS_SUBCLASS_OF_CLASS([kNonEmptyString class], [NSNumber class]);
        })).to.beTruthy();
    });

    it(@"handles same classes correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CLASS_SUBCLASS_OF_CLASS([kNonEmptyString class], [NSString class]);
        })).to.beFalsy();
    });

    it(@"handles non-subclasses correctly", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_CLASS_SUBCLASS_OF_CLASS([kNonEmptyString class], [NSArray class]);
        })).to.beTruthy();
    });

});

describe(@"RZCASSERT_CLASS_SUBCLASS_OF_CLASS works", ^{

    it(@"handles nil correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CLASS_SUBCLASS_OF_CLASS([kNilString class], [NSObject class]);
        })).to.beTruthy();
    });

    it(@"handles classes correctly when you don’t explicitly call +class, or when you pass an object", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CLASS_SUBCLASS_OF_CLASS(kNilString, NSObject);
        })).to.beTruthy();
    });

    it(@"handles non-subclasses correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CLASS_SUBCLASS_OF_CLASS([kNonEmptyString class], [NSNumber class]);
        })).to.beTruthy();
    });

    it(@"handles same classes correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CLASS_SUBCLASS_OF_CLASS([kNonEmptyString class], [NSString class]);
        })).to.beFalsy();
    });

    it(@"handles non-subclasses correctly", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_CLASS_SUBCLASS_OF_CLASS([kNonEmptyString class], [NSArray class]);
        })).to.beTruthy();
    });

});

describe(@"RZASSERT_SUBCLASSES_MUST_OVERRIDE works", ^{

    it(@"always throws an exception", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_SUBCLASSES_MUST_OVERRIDE;
        })).to.beTruthy();
    });
    
});

describe(@"RZASSERT_SHOULD_NEVER_GET_HERE works", ^{
    
    it(@"always throws an exception", ^{
        expect(testAssertionWithBlock(^{
            RZASSERT_SHOULD_NEVER_GET_HERE;
        })).to.beTruthy();
    });
    
});

describe(@"RZCASSERT_SHOULD_NEVER_GET_HERE works", ^{
    
    it(@"always throws an exception", ^{
        expect(testAssertionWithBlock(^{
            RZCASSERT_SHOULD_NEVER_GET_HERE;
        })).to.beTruthy();
    });
    
});

SpecEnd
