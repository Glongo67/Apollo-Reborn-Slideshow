// Media dimensions are distinct from poster dimensions used by grid layout.
#ifndef ApolloGalleryResolution_h
#define ApolloGalleryResolution_h
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreFoundation/CoreFoundation.h>
#import <ImageIO/ImageIO.h>
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
// Orientation-independent HD threshold: at least 720 pixels on both axes.
NS_INLINE NSString * _Nullable ApolloGalleryResolutionQualityText(CGSize size) {
    if (!ApolloGalleryResolutionIsValid(size)) return nil;
    return MIN(size.width, size.height) >= 720.0 ? @"HD" : @"SD";
}

// Read container metadata, without decoding a bitmap. A full-tier image may
// itself have been downsampled for memory, so its rendered size is not proof
// of the source dimensions. Only pass original bytes, never thumbnail bytes.
NS_INLINE CGSize ApolloGalleryResolutionFromImageData(NSData * _Nullable data) {
    if (!data.length) return CGSizeZero;
    CGImageSourceRef source = CGImageSourceCreateWithData((__bridge CFDataRef)data, NULL);
    if (!source) return CGSizeZero;
    NSDictionary *properties = CFBridgingRelease(CGImageSourceCopyPropertiesAtIndex(source, 0, NULL));
    CFRelease(source);
    CGSize size = ApolloGalleryResolutionFromValues(properties[(NSString *)kCGImagePropertyPixelWidth],
                                                    properties[(NSString *)kCGImagePropertyPixelHeight]);
    NSInteger orientation = [properties[(NSString *)kCGImagePropertyOrientation] integerValue];
    if (orientation >= 5 && orientation <= 8) size = CGSizeMake(size.height, size.width);
    return size;
}
#endif
