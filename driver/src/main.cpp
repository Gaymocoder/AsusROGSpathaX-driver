#include "utils/timer.h"
#include "utils/libusb.h"
#include "utils/logger.h"

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

int main(int argc, char** argv)
{
    utils::logger::init(argc, argv);

    TRACE("This is a trace message");
    DEBUG("This is a debug message");
    INFO("This is an info message");
    WARN("This is a warn message");
    ERROR("This is an error message");
    CRITICAL("This is a critical message\n");

    int error = 0;
    libusb_context *ctx = NULL;

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