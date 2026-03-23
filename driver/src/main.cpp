#include "utils/libusb.h"
#include "utils/logger.h"
#include "utils/macro.h"
#include "utils/std.h"

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

int main(int argc, char** argv)
{
    utils::logger::init(argc, argv);
    CRIT_ASSERT(!utils::std::check_root(argc, argv), "Superuser rights are needed to open devices");

    libusb_context *ctx = NULL;
    int error = libusb_init(&ctx);
    CRIT_ASSERT(!error, "Failed to init libusb with {}: {}", libusb_error_name(error), libusb_strerror(error));

    utils::libusb::print_devices(ctx);
    
    libusb_exit(ctx);
    return 0;
}