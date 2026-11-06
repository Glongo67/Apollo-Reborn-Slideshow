// Media dimensions are distinct from poster dimensions used by grid layout.
#ifndef ApolloGalleryResolution_h
#define ApolloGalleryResolution_h
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreFoundation/CoreFoundation.h>
#include <math.h>
#include <limits.h>

NS_INLINE BOOL ApolloGalleryResolutionIsValid(CGSize size) {
    return isfinite(size.width) && isfinite(size.height) &&
        size.width >= 1 && size.height >= 1 && size.width <= INT_MAX && size.height <= INT_MAX;
}

NS_INLINE CGSize ApolloGalleryResolutionFromValues(id _Nullable width, id _Nullable height) {
    if (![width isKindOfClass:NSNumber.class] || ![height isKindOfClass:NSNumber.class] ||
        CFGetTypeID((__bridge CFTypeRef)width) == CFBooleanGetTypeID() ||
        CFGetTypeID((__bridge CFTypeRef)height) == CFBooleanGetTypeID()) return CGSizeZero;
    CGSize size = CGSizeMake([width doubleValue], [height doubleValue]);
    return ApolloGalleryResolutionIsValid(size) ? size : CGSizeZero;
}

NS_INLINE NSString * _Nullable ApolloGalleryResolutionText(CGSize size) {
    if (!ApolloGalleryResolutionIsValid(size)) return nil;
    return [NSString stringWithFormat:@"%.0f × %.0f", (double)size.width, (double)size.height];
}
#endif
