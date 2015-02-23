//
//  RZAssert.h
//  RZAssert
//
//  Created by Michael Gorbach on 7/25/14.
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

@import Foundation;

@interface RZAssert : NSObject

/**
 *  Configures RZAssert to log using a custom handler. This block is run only when @c NS_BLOCK_ASSERTIONS is defined.
 *
 *  @param loggingHandler The block to run when an assertion condition is encountered, but assertions are disabled.
 */
+ (void)configureWithLoggingHandler:(void(^)(NSString *message))loggingHandler;

/**
 *  Logs a message using the RZAssert logging handler. For private use only.
 *
 *  @param format The format string and parameters to log.
 */
+ (void)logMessageWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

@end

#pragma mark - Helpers

#define PRETTY_LOG_MESSAGE_WITH_FORMAT(format, ...) \
    do { \
        [RZAssert logMessageWithFormat:[NSString stringWithFormat:@"**** Assertion failure in %s, %s:%d\n%@", __PRETTY_FUNCTION__, __FILE__, __LINE__, [NSString stringWithFormat:(format), ##__VA_ARGS__]]]; \
    } while(0);

#pragma mark - Basic Assertions

// General Assertions

/**
 *  Assert that an object is not nil.
 *
 *  @param object     An object to compare with nil.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_NIL(object) \
    do { \
        if ( (object) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Nil Assertion **** \nExpected nil, but " #object @" is not nil \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZASSERT_NIL(object) \
    do { \
        NSAssert((object == nil), @"**** Unexpected Nil Assertion **** \nExpected nil, but " #object @" is not nil \nSelf: \"%@\"", self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_NIL(object) \
    do { \
        if ( (object) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Nil Assertion **** \nExpected nil, but " #object @" is not nil \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZCASSERT_NIL(object) \
    do { \
        NSCAssert((object == nil), @"**** Unexpected Nil Assertion **** \nExpected nil, but " #object @" is not nil"); \
    } while(0)
#endif

/**
 *  Assert that an object is nil.
 *
 *  @param object     An object to compare with nil.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_NOT_NIL(object) \
    do { \
        if ( !(object) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Non-Nil Assertion **** \nExpected not nil, but " #object @" is nil \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZASSERT_NOT_NIL(object) \
    do { \
        NSAssert((object), @"**** Unexpected Non-Nil Assertion **** \nExpected not nil, but " #object @" is nil \nSelf: \"%@\"", self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_NOT_NIL(object) \
    do { \
        if ( !(object) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Non-Nil Assertion **** \nExpected not nil, but " #object @" is nil \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZCASSERT_NOT_NIL(object) \
    do { \
        NSCAssert((object), @"**** Unexpected Non-Nil Assertion **** \nExpected not nil, but " #object @" is nil"); \
    } while(0)
#endif

/**
 *  Always assert.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_ALWAYS \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nSelf: \"%@\"", self) \
    } while(0)
#else
#define RZASSERT_ALWAYS \
    do { \
        NSAssert(NO, @"**** Unexpected Assertion **** \nSelf: \"%@\"", self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_ALWAYS \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nSelf: \"%@\"", self) \
    } while(0)
#else
#define RZCASSERT_ALWAYS \
    do { \
        NSCAssert(NO, @"**** Unexpected Assertion ****"); \
    } while(0)
#endif

/**
 *  Assert that a value is truthy (i.e. nonzero).
 *
 *  @param object     An object instance to compare with 0.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_TRUE(test) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZASSERT_TRUE(test) \
    do { \
        NSAssert((test), @"**** Unexpected Assertion **** \nSelf: \"%@\"", self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_TRUE(test) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZCASSERT_TRUE(test) \
    do { \
        NSCAssert((test), @"**** Unexpected Assertion ****"); \
    } while(0)
#endif

/**
 *  Assert than a value is falsy (zero).
 *
 *  @param object     An object instance to compare with 1.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_FALSE(test) \
    do { \
        if ( (test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZASSERT_FALSE(test) \
    do { \
        NSAssert(!(test), @"**** Unexpected Assertion **** \nSelf: \"%@\"", self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_FALSE(test) \
    do { \
        if ( (test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nSelf: \"%@\"", self) \
        } \
    } while(0)
#else
#define RZCASSERT_FALSE(test) \
    do { \
        NSCAssert(!(test), @"**** Unexpected Assertion ****"); \
    } while(0)
#endif

/**
 *  Always assert and log a message.
 *
 *  @param message     A printf-style format string that describes the failure condition.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_WITH_MESSAGE(message, ...) \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], self) \
    } while(0)
#else
#define RZASSERT_WITH_MESSAGE(message, ...) \
    do { \
        NSAssert(NO, @"**** Unexpected Assertion **** %@ \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_WITH_MESSAGE(message, ...) \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], self) \
    } while(0)
#else
#define RZCASSERT_WITH_MESSAGE(message, ...) \
    do { \
        NSCAssert(NO, @"**** Unexpected Assertion **** %@", [NSString stringWithFormat:message, ##__VA_ARGS__]); \
    } while(0)
#endif

/**
 *  Always assert and log a message and the result of an expression.
 *
 *  @param expression  The expression whose result you want to print. Should evaluate to a %@-printable value (an object or nil).
 *  @param message     A printf-style format string that describes the failure condition.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_WITH_MESSAGE_LOG(expression, message, ...) \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nExpression: \"%@\" \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression, self) \
    } while(0)
#else
#define RZASSERT_WITH_MESSAGE_LOG(expression, message, ...) \
    do { \
        NSAssert(NO, @"**** Unexpected Assertion **** %@ \nExpression: \"%@\" \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression, self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_WITH_MESSAGE_LOG(expression, message, ...) \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nExpression: \"%@\" \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression, self) \
    } while(0)
#else
#define RZCASSERT_WITH_MESSAGE_LOG(expression, message, ...) \
    do { \
        NSCAssert(NO, @"**** Unexpected Assertion **** %@ \nExpression: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression); \
    } while(0)
#endif

/**
 *  Assert that a value is truthy (i.e. nonzero), and log a message.
 *
 *  @param test        The value to test.
 *  @param message     A printf-style format string that describes the failure condition.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_TRUE_WITH_MESSAGE(test, message, ...) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], self) \
        } \
    } while(0)
#else
#define RZASSERT_TRUE_WITH_MESSAGE(test, message, ...) \
    do { \
        NSAssert(test, @"**** Unexpected Assertion **** %@ \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_TRUE_WITH_MESSAGE(test, message, ...) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], self) \
        } \
    } while(0)
#else
#define RZCASSERT_TRUE_WITH_MESSAGE(test, message, ...) \
    do { \
        NSCAssert(test, @"**** Unexpected Assertion **** %@", [NSString stringWithFormat:message, ##__VA_ARGS__]); \
    } while(0)
#endif

/**
 *  Asserrt that a value is truthy (i.e. nonzero), and log a message and the result of an expression.
 *
 *  @param test       The value to test.
 *  @param expression The expression whose result you want to print. Should evaluate to a %@-printable value (an object or nil).
 *  @param message    A printf-style format string that describes the failure condition.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_TRUE_WITH_MESSAGE_LOG(test, expression, message, ...) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nReason: \nExpression:\"%@\", \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression, self) \
        } \
    } while(0)
#else
#define RZASSERT_TRUE_WITH_MESSAGE_LOG(test, expression, message, ...) \
    do { \
        NSAssert(test, @"**** Unexpected Assertion **** %@ \nReason: \nExpression:\"%@\", \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression, self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_TRUE_WITH_MESSAGE_LOG(test, expression, message, ...) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** %@ \nReason: \nExpression:\"%@\", \nSelf: \"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression, self) \
        } \
    } while(0)
#else
#define RZCASSERT_TRUE_WITH_MESSAGE_LOG(test, expression, message, ...) \
    do { \
        NSCAssert(test, @"**** Unexpected Assertion **** %@ \nReason: \nExpression:\"%@\"", [NSString stringWithFormat:message, ##__VA_ARGS__], expression); \
    } while(0)
#endif

/**
 *  Assert that a value is truthy (i.e. nonzero), and log a message and the result of an expression.
 *
 *  @param test       The value to test.
 *  @param expression The expression whose result you want to print. Should evaluate to a %@-printable value (an object or nil).
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_TRUE_LOG(test, expression) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nExpression \"%@\" \nSelf: \"%@\"", expression, self) \
        } \
    } while(0)
#else
#define RZASSERT_TRUE_LOG(test, expression) \
    do { \
        NSAssert(test, @"**** Unexpected Assertion **** \nExpression \"%@\" \nSelf: \"%@\"", expression, self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_TRUE_LOG(test, expression) \
    do { \
        if ( !(test) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Assertion **** \nExpression \"%@\" \nSelf: \"%@\"", expression, self) \
        } \
    } while(0)
#else
#define RZCASSERT_TRUE_LOG(test, expression) \
    do { \
        NSCAssert(test, @"**** Unexpected Assertion **** \nExpression \"%@\"", expression); \
    } while(0)
#endif

# pragma mark - Higher-Level Assertions

// Equality Assertions

/**
 *  Assert that x and y are equal object pointers. Uses == to determine equality.
 *
 *  @param x     An object.
 *  @param y     An object.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_EQUAL_OBJECT_POINTERS(x, y) \
    do { \
        if ( (x) != (y) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object Pointers Unexpectedly Unequal **** \nReason: Left: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])) \
        } \
    } while(0)
#else
#define RZASSERT_EQUAL_OBJECT_POINTERS(x, y) \
    do { \
        NSAssert( (x) == (y), @"**** Object Pointers Unexpectedly Unequal **** \nReason: Left: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_EQUAL_OBJECT_POINTERS(x, y) \
    do { \
        if ( (x) != (y) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object Pointers Unexpectedly Unequal **** \nReason: Left: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])) \
        } \
    } while(0)
#else
#define RZCASSERT_EQUAL_OBJECT_POINTERS(x, y) \
    do { \
        NSCAssert( (x) == (y), @"**** Object Pointers Unexpectedly Unequal **** \nReason: Left: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])); \
    } while(0)
#endif

/**
 *  Assert that x and y are nonequal objects. Uses -isEqual: to determine equality.
 *
 *  @param x     An object.
 *  @param y     An object.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_EQUAL_OBJECTS(x, y) \
    do { \
        if ( !( (!(x) && !(y)) || [(x) isEqual:(y)] ) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Objects Unexpectedly Unequal **** \nLeft: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])) \
        } \
    } while(0)
#else
#define RZASSERT_EQUAL_OBJECTS(x, y) \
    do { \
        NSAssert( (!(x) && !(y)) || [(x) isEqual:(y)] , @"**** Objects Unexpectedly Unequal **** \nLeft: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_EQUAL_OBJECTS(x, y) \
    do { \
        if ( !( (!(x) && !(y)) || [(x) isEqual:(y)] ) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Objects Unexpectedly Unequal **** \nLeft: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])) \
        } \
    } while(0)
#else
#define RZCASSERT_EQUAL_OBJECTS(x, y) \
    do { \
        NSCAssert( (!(x) && !(y)) || [(x) isEqual:(y)] , @"**** Objects Unexpectedly Unequal **** \nLeft: \"%@\" of class \"%@\", Right: \"%@\" of class \"%@\"", x, NSStringFromClass([x class]), y, NSStringFromClass([y class])); \
    } while(0)
#endif

// String Assertions

/**
 *  Assert that x and y are equal strings. -isEqualToString: is used to determine equality.
 *
 *  @param x     An NSString instance.
 *  @param y     An NSString instance.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_EQUAL_STRINGS(x, y) \
    do { \
        if ( !( (!(x) && !(y)) || [(x) isEqualToString:(y)] ) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Strings Unexpectedly Unequal **** \nLeft: \"%@\"\nRight: \"%@\"", x, y) \
        } \
    } while(0)
#else
#define RZASSERT_EQUAL_STRINGS(x, y) \
    do { \
        NSAssert( (!(x) && !(y)) || [(x) isEqualToString:(y)] , @"**** Strings Unexpectedly Unequal **** \nLeft: \"%@\"\nRight: \"%@\"", x, y); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_EQUAL_STRINGS(x, y) \
    do { \
        if ( !( (!(x) && !(y)) || [(x) isEqualToString:(y)] ) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Strings Unexpectedly Unequal **** \nLeft: \"%@\"\nRight: \"%@\"", x, y) \
        } \
    } while(0)
#else
#define RZCASSERT_EQUAL_STRINGS(x, y) \
    do { \
        NSCAssert( (!(x) && !(y)) || [(x) isEqualToString:(y)] , @"**** Strings Unexpectedly Unequal **** \nLeft: \"%@\"\nRight: \"%@\"", x, y); \
    } while(0)
#endif

/**
 *  Assert that a string is non-nil and not equal to the empty string.
 *
 *  @param string An NSString instance.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_NONEMPTY_STRING(string) \
    do { \
        if ( !( (string) != nil && [(string) isKindOfClass:[NSString class]] && [(string) length] > 0 ) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Nil, Wrong Class, or Empty String **** \nReason: Expected non-empty string but got: \"%@\" \nSelf: \"%@\"", string, self) \
        } \
    } while(0)
#else
#define RZASSERT_NONEMPTY_STRING(string) \
    do { \
        NSAssert((string) != nil && [(string) isKindOfClass:[NSString class]] && [(string) length] > 0, @"**** Unexpected Nil, Wrong Class, or Empty String **** \nReason: Expected non-empty string but got: \"%@\" \nSelf: \"%@\"", string, self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_NONEMPTY_STRING(string) \
    do { \
        if ( !( (string) != nil && [(string) isKindOfClass:[NSString class]] && [(string) length] > 0 ) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Unexpected Nil, Wrong Class, or Empty String **** \nReason: Expected non-empty string but got: \"%@\" \nSelf: \"%@\"", string, self) \
        } \
    } while(0)
#else
#define RZCASSERT_NONEMPTY_STRING(string) \
    do { \
        NSCAssert((string) != nil && [(string) isKindOfClass:[NSString class]] && [(string) length] > 0, @"**** Unexpected Nil, Wrong Class, or Empty String **** \nReason: Expected non-empty string but got: \"%@\"", string); \
    } while(0)
#endif

// Type Checks

/**
 *  Assert that an object is an instance of TestClass.
 *
 *  @param object        An object.
 *  @param TestClass     A class. May be passed as either TestClass or [TestClass class].
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_KINDOF(object, TestClass) \
    do { \
        if ( ![(object) isKindOfClass:[TestClass class]] ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object of Unexpected Class **** \nReason: Expected class: \"%@\" but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])) \
        } \
    } while(0)
#else
#define RZASSERT_KINDOF(object, TestClass) \
    do { \
        NSAssert([(object) isKindOfClass:[TestClass class]], @"**** Object of Unexpected Class **** \nReason: Expected class: \"%@\" but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_KINDOF(object, TestClass) \
    do { \
        if ( ![(object) isKindOfClass:[TestClass class]] ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object of Unexpected Class **** \nReason: Expected class: \"%@\" but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])) \
        } \
    } while(0)
#else
#define RZCASSERT_KINDOF(object, TestClass) \
    do { \
        NSCAssert([(object) isKindOfClass:[TestClass class]], @"**** Object of Unexpected Class **** \nReason: Expected class: \"%@\" but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])); \
    } while(0)
#endif

/**
 *  Assert that an object is either and instance of TestClass, or is nil.
 *
 *  @param object        An object.
 *  @param TestClass     A class. May be passed as either TestClass or [TestClass class].
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_KINDOF_OR_NIL(object, TestClass) \
    do { \
        if ( !([(object) isKindOfClass:[TestClass class]] || (object) == nil) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object of Unexpected Class and Not Nil **** \nReason: Expected class: \"%@\" or nil but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])) \
        } \
    } while(0)
#else
#define RZASSERT_KINDOF_OR_NIL(object, TestClass) \
    do { \
        NSAssert([(object) isKindOfClass:[TestClass class]] || (object) == nil, @"**** Object of Unexpected Class and Not Nil **** \nReason: Expected class: \"%@\" or nil but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_KINDOF_OR_NIL(object, TestClass) \
    do { \
        if ( !([(object) isKindOfClass:[TestClass class]] || (object) == nil) ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object of Unexpected Class and Not Nil **** \nReason: Expected class: \"%@\" or nil but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])) \
        } \
    } while(0)
#else
#define RZCASSERT_KINDOF_OR_NIL(object, TestClass) \
    do { \
        NSCAssert([(object) isKindOfClass:[TestClass class]] || (object) == nil, @"**** Object of Unexpected Class and Not Nil **** \nReason: Expected class: \"%@\" or nil but got: \"%@\" of class \"%@\"", NSStringFromClass(TestClass), object, NSStringFromClass([object class])); \
    } while(0)
#endif

/**
 *  Assert that an object's class conforms to a protocol.
 *
 *  @param object        An object.
 *  @param protocol      A protocol to use to test the object. Pass as @protocol(someProtocol)
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_CONFORMS_PROTOCOL(object, protocol) \
    do { \
        if ( ![(object) conformsToProtocol:protocol] ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object Unexpectedly Doesn't Conform to Protocol **** \nReason: Expected object: \"%@\" of class \"%@\" to conform to protocol \"%@\", but it does not.", object, NSStringFromClass([object class]), NSStringFromProtocol(protocol)) \
        } \
    } while(0)
#else
#define RZASSERT_CONFORMS_PROTOCOL(object, protocol) \
    do { \
        NSAssert([(object) conformsToProtocol:protocol], @"**** Object Unexpectedly Doesn't Conform to Protocol **** \nReason: Expected object: \"%@\" of class \"%@\" to conform to protocol \"%@\", but it does not.", object, NSStringFromClass([object class]), NSStringFromProtocol(protocol)); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_CONFORMS_PROTOCOL(object, protocol) \
    do { \
        if ( ![(object) conformsToProtocol:protocol] ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Object Unexpectedly Doesn't Conform to Protocol **** \nReason: Expected object: \"%@\" of class \"%@\" to conform to protocol \"%@\", but it does not.", object, NSStringFromClass([object class]), NSStringFromProtocol(protocol)) \
        } \
    } while(0)
#else
#define RZCASSERT_CONFORMS_PROTOCOL(object, protocol) \
    do { \
        NSCAssert([(object) conformsToProtocol:protocol], @"**** Object Unexpectedly Doesn't Conform to Protocol **** \nReason: Expected object: \"%@\" of class \"%@\" to conform to protocol \"%@\", but it does not.", object, NSStringFromClass([object class]), NSStringFromProtocol(protocol)); \
    } while(0)
#endif


/**
 *  Assert that a class is a subclass of another class.
 *
 *  @param Subclass        A subclass.
 *  @param Superclass     A superclass.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_CLASS_SUBCLASS_OF_CLASS(Subclass, Superclass) \
    do { \
        if ( ![(Subclass) isSubclassOfClass:(Superclass)] ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Bad Subclass Relationship **** \nReason: Expected class: \"%@\" to be a subclass of class: \"%@\", but it is not.", Subclass, Superclass) \
        } \
    } while(0)
#else
#define RZASSERT_CLASS_SUBCLASS_OF_CLASS(Subclass, Superclass) \
    do { \
        NSAssert([(Subclass) isSubclassOfClass:(Superclass)], @"**** Bad Subclass Relationship **** \nReason: Expected class: \"%@\" to be a subclass of class: \"%@\", but it is not.", Subclass, Superclass); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_CLASS_SUBCLASS_OF_CLASS(Subclass, Superclass) \
    do { \
        if ( ![(Subclass) isSubclassOfClass:(Superclass)] ) { \
            PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Bad Subclass Relationship **** \nReason: Expected class: \"%@\" to be a subclass of class: \"%@\", but it is not.", Subclass, Superclass) \
        } \
    } while(0)
#else
#define RZCASSERT_CLASS_SUBCLASS_OF_CLASS(Subclass, Superclass) \
    do { \
        NSCAssert([(Subclass) isSubclassOfClass:(Superclass)], @"**** Bad Subclass Relationship **** \nReason: Expected class: \"%@\" to be a subclass of class: \"%@\", but it is not.", Subclass, Superclass); \
    } while(0)
#endif

// Overrides

/**
 *  Always assert. Print out messages that indicate that a child class should have overridden this method.
 *
 * Place RZASSERT_SUBCLASSES_MUST_OVERRIDE in a superclass method that would
 * otherwise be left empty
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_SUBCLASSES_MUST_OVERRIDE \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Subclass Responsibility Assertion **** \nReason: Subclasses of %@ MUST override this method: %@", NSStringFromClass([self class]), NSStringFromSelector(_cmd)) \
    } while(0)
#else
#define RZASSERT_SUBCLASSES_MUST_OVERRIDE \
    do { \
        NSAssert(NO, @"**** Subclass Responsibility Assertion **** \nReason: Subclasses of %@ MUST override this method: %@", NSStringFromClass([self class]), NSStringFromSelector(_cmd)); \
    } while(0)
#endif

// No RZCASSERT_SUBCLASSES_MUST_OVERRIDE variant. It wouldn't make sense.

// Should-never-get-here

/**
 *  Always assert. Use to indicate that a code path should not be reachable in production.
 */

#if defined(NS_BLOCK_ASSERTIONS)
#define RZASSERT_SHOULD_NEVER_GET_HERE \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Assertion: Should Never Get Here **** \nSelf: \"%@\"", self) \
    } while(0)
#else
#define RZASSERT_SHOULD_NEVER_GET_HERE \
    do { \
        NSAssert(NO, @"**** Assertion: Should Never Get Here **** \nSelf: \"%@\"", self); \
    } while(0)
#endif

#if defined(NS_BLOCK_ASSERTIONS)
#define RZCASSERT_SHOULD_NEVER_GET_HERE \
    do { \
        PRETTY_LOG_MESSAGE_WITH_FORMAT(@"**** Assertion: Should Never Get Here **** \nSelf: \"%@\"", self) \
    } while(0)
#else
#define RZCASSERT_SHOULD_NEVER_GET_HERE \
    do { \
        NSCAssert(NO, @"**** Assertion: Should Never Get Here ****"); \
    } while(0)
#endif

#pragma mark - Block Assertions

/**
 *  NS_BLOCK_ASSERTIONS is defined only in the Release config. It refers to blocking
 *  assertion from being added to released code, rather than assertions relating to 
 *  Objective-C blocks.
 *
 */

#if !defined(NS_BLOCK_ASSERTIONS)

#define RZASSERT_BLOCK(condition, desc, ...) \
do { \
if ( !(condition) ) { \
    [[NSAssertionHandler currentHandler] handleFailureInFunction:NSStringFromSelector(_cmd) \
                                                            file:[NSString stringWithUTF8String:__FILE__] \
                                                      lineNumber:__LINE__ \
                                                     description:(desc), ##__VA_ARGS__]; \
    }\
} while(0);

#else // NS_BLOCK_ASSERTIONS defined

#define RZASSERT_BLOCK(condition, desc, ...)

#endif
