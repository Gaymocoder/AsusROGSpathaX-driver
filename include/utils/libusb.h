#include <libusb-1.0/libusb.h>

int check_root();

int libusb_open_device(libusb_device* device, libusb_device_handle** handle);

int libusb_print_device(libusb_device* device);

void libusb_print_devices(libusb_context* ctx);