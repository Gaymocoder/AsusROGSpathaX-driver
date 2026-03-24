#include "utils/libusb.h"
#include "utils/logger.h"
#include "utils/std.h"

#include <signal.h>
#include <sys/ioctl.h>

#define VENDOR_ID  0x0b05
#define PRODUCT_ID 0x1977

int main(int argc, char** argv)
{
    utils::logger::init(argc, argv);
    int error = utils::std::check_root(argc, argv);
    CRIT_ASSERT(!error, "Superuser rights are needed to open devices");

    int parent_pid = utils::std::get_argv_parent_pid(argc, argv);
    if (!error && parent_pid)
    {
        WARN("Child: Killing parent with pid{}", parent_pid);
        kill(parent_pid, 1);
    }

    libusb_context *ctx = NULL;
    error = libusb_init(&ctx);
    CRIT_ASSERT(!error, "Failed to init libusb with {}: {}", libusb_error_name(error), libusb_strerror(error));

    utils::libusb::print_devices(ctx);
    
    libusb_exit(ctx);
    DEBUG("App finished its work successfully, returning 0");
    if (parent_pid) ioctl(STDIN_FILENO, TIOCSTI, "\n");
    return 0;
}