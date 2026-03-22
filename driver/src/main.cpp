#include "utils/timer.h"
#include "utils/libusb.h"
#include "utils/logger.h"
#include "utils/macro.h"

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

int main(int argc, char** argv)
{
    utils::logger::init(argc, argv);
    libusb_context *ctx = NULL;

    int error = libusb_init(&ctx);
    gcs_assert(!error, "Failed to init libusb with {}: {}\n", libusb_error_name(error), libusb_strerror(error));

    utils::libusb::print_devices(ctx);
    
    libusb_exit(ctx);
    return 0;
}