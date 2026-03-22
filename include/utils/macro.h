#ifndef __AROGSX_UTILS_MACRO_H__
#define __AROGSX_UTILS_MACRO_H__

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

#define gcs_assert(cond, fmt, ...) \
    if (!cond) { \
        CRITICAL(fmt __VA_OPT__(,) __VA_ARGS__); \
        return 1; \
    }

#endif