#ifndef __AROGSX_UTILS_MACRO_H__
#define __AROGSX_UTILS_MACRO_H__

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

#define CRIT_ASSERT(cond, fmt, ...) \
    if (!cond) { \
         \
        CRITICAL(fmt ", aborting" __VA_OPT__(,) __VA_ARGS__); \
        abort(); \
    }

#define ASSERT(cond, fmt, ...) \
    if (!cond) { \
        ERROR(fmt __VA_OPT__(,) __VA_ARGS__); \
        return 1; \
    }

#define SUCCESS(cond, fmt, ...) \
    if (cond) { \
        TRACE(fmt __VA_OPT__(,) __VA_ARGS__); \
        return 0; \
    }

#endif