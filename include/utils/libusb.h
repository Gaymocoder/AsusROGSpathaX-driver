#ifndef __AROGSX_UTILS_LIBUSB_H__
#define __AROGSX_UTILS_LIBUSB_H__

#include <libusb-1.0/libusb.h>

namespace utils::libusb
{
    int print_device(libusb_device* device);
    int print_devices(libusb_context* ctx);
}

#endif