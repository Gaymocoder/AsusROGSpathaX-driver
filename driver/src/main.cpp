#include "utils/timer.h"
#include "utils/libusb.h"

#include <spdlog/spdlog.h>

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

int main(int argc, char** argv)
{
    int error = 0;
    libusb_context *ctx = NULL;

    spdlog::set_level(spdlog::level::trace);
    error = libusb_init(&ctx);
    if (error) 
    {
        fprintf(stderr, "Failed to init libusb with %s: %s\n", libusb_error_name(error), libusb_strerror(error));
        return 1;
    }

    utils::libusb::print_devices(ctx);
    
    libusb_exit(ctx);
    return 0;
}