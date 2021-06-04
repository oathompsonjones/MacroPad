add_executable(
    macro_pad
    usb_descriptors.c
    MacroPad.cpp
    main.cpp
)

# Pull in pico libraries that we need
target_link_libraries(macro_pad pico_stdlib pico_rgb_keypad)

# create map/bin/hex file etc.
pico_add_extra_outputs(macro_pad)

# TINY USB STUFF
target_include_directories(macro_pad PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(macro_pad pico_stdlib tinyusb_device tinyusb_board)
pico_add_extra_outputs(macro_pad)

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(macro_pad pico_stdlib)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(macro_pad)