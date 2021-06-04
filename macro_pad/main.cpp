#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"
#include "pico_rgb_keypad.hpp"

#include "MacroPad.cpp"

using namespace pimoroni;
PicoRGBKeypad keypad;
MacroPad macropad;

uint16_t button_states = 0;
uint16_t last_button_states = 0;

int main()
{
    tusb_init();
    board_init();
    keypad.init();
    keypad.set_brightness(0.25);
    macropad.resetColours();

    while (true)
    {
        const uint32_t interval_ms = 10;
        static uint32_t start_ms = 0;
        if (board_millis() - start_ms >= interval_ms)
        {
            start_ms += interval_ms;

            if (tud_suspended())
                tud_remote_wakeup();

            if (tud_hid_ready())
            {
                button_states = keypad.get_button_states();
                int button = 0;
                if (!button_states)
                    button = -1;
                else if (last_button_states != button_states)
                {
                    unsigned int number = button_states;
                    while (number >>= 1)
                        ++button;

                    if (button > -1)
                        macropad.buttonDown(button);
                }
                else
                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            }
        }

        tud_task();
        last_button_states = button_states;
    }

    return 0;
}

uint16_t tud_hid_get_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    return 0;
}

void tud_hid_set_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
}
