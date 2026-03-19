#ifndef __AROGSX_UTILS_LIBUSB_H__
#define __AROGSX_UTILS_LIBUSB_H__

#include <libusb-1.0/libusb.h>

namespace utils::libusb
{
    int open_device(libusb_device* device, libusb_device_handle** handle);
    int print_device(libusb_device* device);
    void print_devices(libusb_context* ctx);
}

#endif