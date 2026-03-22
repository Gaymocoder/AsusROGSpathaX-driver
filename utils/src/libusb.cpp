#include "utils/logger.h"
#include "utils/libusb.h"
#include "utils/std.h"

#include <limits>

#include <unistd.h>

namespace utils::libusb
{

int open_device(libusb_device* device, libusb_device_handle** handle)
{
    root_needed_operation:
    int error = libusb_open(device, handle);
    switch(error)
    {
        case LIBUSB_SUCCESS:
            return 0;

        case LIBUSB_ERROR_ACCESS:
            ASSERT(!utils::std::check_root(), "Superuser rights are needed to open devices");
            goto root_needed_operation;

        default:
            ERROR("Failed to open usb_device with {}: {}", libusb_error_name(error), libusb_strerror(error));
            return 2;
    }
}

int print_device(libusb_device* device)
{
    libusb_device_handle* handle = NULL;
    int error = open_device(device, &handle);
    ASSERT(!error, "Failed to open device with {}: {}\n", libusb_error_name(error), libusb_strerror(error));

    libusb_device_descriptor dscr;
    memset(&dscr, 0, sizeof(dscr));
    libusb_get_device_descriptor(device, &dscr);
    
    unsigned char str_model[64];
    unsigned char str_vendor[64];
    memset(str_model, 0, sizeof(str_model));
    memset(str_vendor, 0, sizeof(str_vendor));
    libusb_get_string_descriptor_ascii(handle, dscr.iProduct, str_model, sizeof(str_model));
    libusb_get_string_descriptor_ascii(handle, dscr.iManufacturer, str_vendor, sizeof(str_vendor));
    
    INFO("Found device: {}", (void*) device);
    INFO("Vendor: {:#06x} {}", dscr.idVendor, (char*) str_vendor);
    INFO("Product: {:#06x} {}\n", dscr.idProduct, (char*) str_model);

    libusb_close(handle);

    return 0;
}

void print_devices(libusb_context* ctx)
{
    libusb_device** devs = NULL;
    ssize_t n = libusb_get_device_list(ctx, &devs);
    for(ssize_t i = 0; i < n; ++i)
        if (print_device(devs[i]))
            continue;
    libusb_free_device_list(devs, 0);
}

}