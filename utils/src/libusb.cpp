#include "utils/logger.h"
#include "utils/libusb.h"
#include "utils/std.h"

#include <limits>

#include <unistd.h>
#include <sys/ioctl.h>

namespace utils::libusb
{

int print_device(libusb_device* device)
{
    libusb_device_handle* handle = NULL;
    int error = libusb_open(device, &handle);
    ASSERT(!error, "Failed to open USB device with {}: {}\n", libusb_error_name(error), libusb_strerror(error));
    TRACE("Opened device successfully ({})", (void*) device);

    libusb_device_descriptor dscr;
    memset(&dscr, 0, sizeof(dscr));
    libusb_get_device_descriptor(device, &dscr);
    TRACE("Got the device's descriptor");
    
    unsigned char str_model[64];
    unsigned char str_vendor[64];
    memset(str_model, 0, sizeof(str_model));
    memset(str_vendor, 0, sizeof(str_vendor));
    libusb_get_string_descriptor_ascii(handle, dscr.iProduct, str_model, sizeof(str_model));
    libusb_get_string_descriptor_ascii(handle, dscr.iManufacturer, str_vendor, sizeof(str_vendor));
    
    DEBUG("Found USB {}.{} device", ((uint8_t) (*(((char*) &(dscr.bcdUSB)) + 1))), ((uint8_t) dscr.bcdUSB) >> 4);
    INFO("Vendor: {:#06x} {}", dscr.idVendor, (char*) str_vendor);
    INFO("Product: {:#06x} {}\n", dscr.idProduct, (char*) str_model);

    libusb_close(handle);

    return 0;
}

int print_devices(libusb_context* ctx)
{
    write(STDOUT_FILENO, "\n", 1);
    TRACE("Getting USB device list to print it... ");

    libusb_device** devs = NULL;
    ssize_t n = libusb_get_device_list(ctx, &devs);
    ASSERT(devs != NULL, "Failed to get device list with {}:  {}", libusb_error_name(n), libusb_strerror(n));

    DEBUG("Found {} USB devices. Printing\n", n);
    for(ssize_t i = 0; i < n; ++i)
        if (print_device(devs[i]))
            continue;
    libusb_free_device_list(devs, 0);
    return 0;
}

}