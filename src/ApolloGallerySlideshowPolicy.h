// Shared, platform-independent slideshow decisions. No duration-based video timeout.
#ifndef ApolloGallerySlideshowPolicy_h
#define ApolloGallerySlideshowPolicy_h
#include <stdbool.h>
#include <stddef.h>

static inline bool ApolloGallerySlideshowCanAdvance(bool video, bool finished,
                                                    bool imageReady, double now,
                                                    double deadline) {
    return video ? finished : (imageReady && now >= deadline);
}

// SIZE_MAX means there is no destination; a single item loops to itself.
static inline size_t ApolloGallerySlideshowNextIndex(size_t current, size_t count) {
    return count == 0 ? (size_t)-1 : (current >= count - 1 ? 0 : current + 1);
}
#endif
