// Post dates shared by gallery metadata and tile captions. Foundation-only.
#ifndef ApolloGalleryPostDate_h
#define ApolloGalleryPostDate_h
#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#include <math.h>

NS_INLINE NSDate * _Nullable ApolloGalleryPostDateFromTimestamp(id _Nullable value) {
    if (![value isKindOfClass:NSNumber.class] ||
        CFGetTypeID((__bridge CFTypeRef)value) == CFBooleanGetTypeID()) return nil;
    NSTimeInterval seconds = [value doubleValue];
    // Reddit's created_utc is Unix seconds. Reject absent/invalid values and
    // dates outside the four-digit-year range instead of showing 01.01.1970.
    if (!isfinite(seconds) || seconds <= 0 || seconds > 253402300799.0) return nil;
    return [NSDate dateWithTimeIntervalSince1970:seconds];
}

// Used only from the main-thread tile configuration path; one formatter per
// process, not one expensive formatter per image. Respect the device timezone.
NS_INLINE NSString * _Nullable ApolloGalleryPostDateText(NSDate * _Nullable date) {
    if (!date) return nil;
    static NSDateFormatter *formatter;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        formatter = [[NSDateFormatter alloc] init];
        formatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"];
        formatter.calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
        formatter.dateFormat = @"dd.MM.yyyy";
    });
    formatter.timeZone = NSTimeZone.defaultTimeZone;
    return [formatter stringFromDate:date];
}
#endif
