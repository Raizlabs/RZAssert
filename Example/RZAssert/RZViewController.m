//
//  RZViewController.m
//  RZAssert
//
//  Created by Raizlabs on 11/24/2014.
//  Copyright (c) 2014 Raizlabs. All rights reserved.
//

#import "RZViewController.h"
#import "RZViewControllerSubclass.h"
#import <RZAssert/RZAssert.h>

@interface RZViewController ()

@end

@implementation RZViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    [self assertTrue];

    [self assertFalse];

    [self assertNil];

    [self assertNotNil:self];

    RZViewControllerSubclass *rzViewControllerSubclass = [[RZViewControllerSubclass alloc] init];

    [rzViewControllerSubclass methodThatSubclassesMustOverride];
}

#pragma mark - RZASSERT_TRUE

- (void)assertTrue
{
    RZASSERT_TRUE(YES);
}

#pragma mark - RZASSERT_FALSE

- (void)assertFalse
{
    RZASSERT_FALSE(NO);
}

#pragma mark - RZASSERT_NIL

- (void)assertNil
{
    RZASSERT_NIL(nil);
}

#pragma mark - RZASSERT_NOT_NIL

- (void)assertNotNil:(id)obj
{
    RZASSERT_NOT_NIL(obj);
}

#pragma mark - RZASSERT_NONEMPTY_STRING

- (void)assertNonEmptyString:(NSString *)nonEmptyString
{
    RZASSERT_NONEMPTY_STRING(nonEmptyString);
}

#pragma mark - RZASSERT_SUBCLASSES_MUST_OVERRIDE

- (void)methodThatSubclassesMustOverride
{
    RZASSERT_SUBCLASSES_MUST_OVERRIDE;
}

#pragma mark - Actions

- (IBAction)throwAssertionRZAssertTrue:(id)sender
{
    RZASSERT_TRUE(NO);
}

- (IBAction)throwAssertionRZAssertFalse:(id)sender
{
    RZASSERT_FALSE(YES);
}

- (IBAction)throwAssertionRZAssertNil:(id)sender
{
    RZASSERT_NIL(self);
}

- (IBAction)throwAssertionRZAssertNotNil:(id)sender
{
    RZASSERT_NOT_NIL(nil);
}

- (IBAction)throwAssertionRZAssertNonEmptyString:(id)sender
{
    RZASSERT_NONEMPTY_STRING(@"");
}

- (IBAction)throwAssertionRZAssertSubclassesMustOverride:(id)sender
{
    RZASSERT_SUBCLASSES_MUST_OVERRIDE;
}

- (IBAction)throwAssertionRZAssertShouldNeverGetHere:(id)sender
{
    RZASSERT_SHOULD_NEVER_GET_HERE;
}

- (IBAction)throwEqualObjectPointerAssertion:(id)sender
{
    RZASSERT_EQUAL_OBJECT_POINTERS(self, sender);
}

@end
