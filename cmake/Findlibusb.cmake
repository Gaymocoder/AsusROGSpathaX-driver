find_path(LIBUSB_INCLUDE_DIR
  NAMES        libusb.h
  PATH_SUFFIXES libusb-1.0
)

find_library(LIBUSB_LIBRARY
  NAMES usb-1.0 usb
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libusb
  REQUIRED_VARS LIBUSB_LIBRARY LIBUSB_INCLUDE_DIR
)

if(LIBUSB_FOUND AND NOT TARGET libusb::libusb)
  add_library(libusb::libusb UNKNOWN IMPORTED)
  set_target_properties(libusb::libusb PROPERTIES
    IMPORTED_LOCATION "${LIBUSB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBUSB_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(LIBUSB_INCLUDE_DIR LIBUSB_LIBRARY)