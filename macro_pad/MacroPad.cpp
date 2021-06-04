#include <list>
#include <math.h>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "pico_rgb_keypad.hpp"

using namespace pimoroni;
extern PicoRGBKeypad keypad;

struct DiscordStates
{
    bool isMuted;
    bool isDeafened;
    bool wasMutedBeforeDeafened;
};

class MacroPad
{
private:
    int mode = 0;
    DiscordStates discordStates = {false, false, false};
    void calcXY(int i, int &x, int &y)
    {
        x = i % keypad.WIDTH;
        y = i / keypad.WIDTH;
    }
    int calcI(int x, int y)
    {
        return y * keypad.WIDTH + x;
    }
    std::list<int> findSquare(int x, int y, int distance)
    {
        std::list<int> coords;
        for (int i = 0; i < keypad.NUM_PADS; ++i)
        {
            int thisX;
            int thisY;
            calcXY(i, thisX, thisY);
            bool a = abs(x - thisX) == distance || abs(y - thisY) == distance;
            bool b = thisY > y + distance || thisY < y - distance;
            bool c = thisX > x + distance || thisX < x - distance;
            if (a && !b && !c)
                coords.push_front(calcI(thisX, thisY));
        }
        return coords;
    }
    void animate(int i)
    {
        int x;
        int y;
        calcXY(i, x, y);
        std::list<int> coords;

        keypad.clear();
        keypad.update();
        sleep_ms(100);

        for (int j = 0; j < 4; ++j)
        {
            coords = findSquare(x, y, j);
            for (int i : coords)
            {
                switch (mode)
                {
                case 0:
                    keypad.illuminate(i, 0, 0, 255);
                    break;
                case 1:
                    keypad.illuminate(i, 255, 0, 0);
                    break;
                case 2:
                    keypad.illuminate(i, 0, 255, 0);
                    break;
                case 3:
                    keypad.illuminate(i, 255, 255, 255);
                    break;
                }
            }
            keypad.update();
            sleep_ms(100);
            keypad.clear();
            keypad.update();
        }

        sleep_ms(100);
        resetColours();
    }
    void pressKey(int Keycode, int ModifierKeys, bool MediaKey = false)
    {
        if (MediaKey)
        {
            uint16_t CodeToUse = Keycode;
            tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &CodeToUse, 2);
        }
        else
        {
            uint8_t CodeToUse[6] = {(uint8_t)Keycode, 0, 0, 0, 0, 0};
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, ModifierKeys, CodeToUse);
        }
    }
    void flashButton(int button)
    {
        keypad.illuminate(button, 255, 0, 0);
        keypad.update();
        sleep_ms(250);
    }

public:
    void resetColours()
    {
        switch (mode)
        {
        case 0:
            // Discord Toggle Mute
            if (discordStates.isMuted)
                keypad.illuminate(0, 255, 0, 0);
            else
                keypad.illuminate(0, 0, 255, 0);
            // Section Screenshot
            keypad.illuminate(1, 0, 255, 0);
            // Not Set
            keypad.illuminate(2, 0, 0, 255);
            // Not Set
            keypad.illuminate(3, 0, 0, 255);
            // Discord Toggle Deafen
            if (discordStates.isDeafened)
                keypad.illuminate(4, 255, 0, 0);
            else
                keypad.illuminate(4, 0, 255, 0);
            // Full Screen Screenshot
            keypad.illuminate(5, 0, 255, 0);
            // Not Set
            keypad.illuminate(6, 0, 0, 255);
            // Not Set
            keypad.illuminate(7, 0, 0, 255);
            // Not Set
            keypad.illuminate(8, 0, 0, 255);
            // Touch Bar Screenshot
            keypad.illuminate(9, 0, 255, 0);
            // Not Set
            keypad.illuminate(10, 0, 0, 255);
            // Not Set
            keypad.illuminate(11, 0, 0, 255);
            // Mode 0
            keypad.illuminate(12, 0, 0, 255);
            // Mode 1
            keypad.illuminate(13, 0, 0, 0);
            // Mode 2
            keypad.illuminate(14, 0, 0, 0);
            // Mode 3
            keypad.illuminate(15, 0, 0, 0);
            break;
        case 1:
            // Not Set
            keypad.illuminate(0, 0, 0, 255);
            // Not Set
            keypad.illuminate(1, 0, 0, 255);
            // Not Set
            keypad.illuminate(2, 0, 0, 255);
            // Not Set
            keypad.illuminate(3, 0, 0, 255);
            // Not Set
            keypad.illuminate(4, 0, 0, 255);
            // Not Set
            keypad.illuminate(5, 0, 0, 255);
            // Not Set
            keypad.illuminate(6, 0, 0, 255);
            // Not Set
            keypad.illuminate(7, 0, 0, 255);
            // Not Set
            keypad.illuminate(8, 0, 0, 255);
            // Not Set
            keypad.illuminate(9, 0, 0, 255);
            // Not Set
            keypad.illuminate(10, 0, 0, 255);
            // Not Set
            keypad.illuminate(11, 0, 0, 255);
            // Mode 0
            keypad.illuminate(12, 0, 0, 0);
            // Mode 1
            keypad.illuminate(13, 0, 0, 255);
            // Mode 2
            keypad.illuminate(14, 0, 0, 0);
            // Mode 3
            keypad.illuminate(15, 0, 0, 0);
            break;
        case 2:
            // Not Set
            keypad.illuminate(0, 0, 0, 255);
            // Not Set
            keypad.illuminate(1, 0, 0, 255);
            // Not Set
            keypad.illuminate(2, 0, 0, 255);
            // Not Set
            keypad.illuminate(3, 0, 0, 255);
            // Not Set
            keypad.illuminate(4, 0, 0, 255);
            // Not Set
            keypad.illuminate(5, 0, 0, 255);
            // Not Set
            keypad.illuminate(6, 0, 0, 255);
            // Not Set
            keypad.illuminate(7, 0, 0, 255);
            // Not Set
            keypad.illuminate(8, 0, 0, 255);
            // Not Set
            keypad.illuminate(9, 0, 0, 255);
            // Not Set
            keypad.illuminate(10, 0, 0, 255);
            // Not Set
            keypad.illuminate(11, 0, 0, 255);
            // Mode 0
            keypad.illuminate(12, 0, 0, 0);
            // Mode 1
            keypad.illuminate(13, 0, 0, 0);
            // Mode 2
            keypad.illuminate(14, 0, 0, 255);
            // Mode 3
            keypad.illuminate(15, 0, 0, 0);
            break;
        case 3:
            // Not Set
            keypad.illuminate(0, 0, 0, 255);
            // Not Set
            keypad.illuminate(1, 0, 0, 255);
            // Not Set
            keypad.illuminate(2, 0, 0, 255);
            // Not Set
            keypad.illuminate(3, 0, 0, 255);
            // Not Set
            keypad.illuminate(4, 0, 0, 255);
            // Not Set
            keypad.illuminate(5, 0, 0, 255);
            // Not Set
            keypad.illuminate(6, 0, 0, 255);
            // Not Set
            keypad.illuminate(7, 0, 0, 255);
            // Not Set
            keypad.illuminate(8, 0, 0, 255);
            // Not Set
            keypad.illuminate(9, 0, 0, 255);
            // Not Set
            keypad.illuminate(10, 0, 0, 255);
            // Not Set
            keypad.illuminate(11, 0, 0, 255);
            // Mode 0
            keypad.illuminate(12, 0, 0, 0);
            // Mode 1
            keypad.illuminate(13, 0, 0, 0);
            // Mode 2
            keypad.illuminate(14, 0, 0, 0);
            // Mode 3
            keypad.illuminate(15, 0, 0, 255);
            break;
        }
        keypad.update();
    }
    void buttonDown(int button)
    {
        switch (mode)
        {
        case 0:
            switch (button)
            {
            case 0:
                // Discord Toggle Mute
                pressKey(HID_KEY_M, KEYBOARD_MODIFIER_LEFTCTRL + KEYBOARD_MODIFIER_LEFTSHIFT + KEYBOARD_MODIFIER_LEFTALT + KEYBOARD_MODIFIER_LEFTGUI);
                discordStates.isDeafened = false;
                discordStates.isMuted = !discordStates.isMuted;
                discordStates.wasMutedBeforeDeafened = discordStates.isMuted;
                break;
            case 1:
                // Section Screenshot
                pressKey(HID_KEY_4, KEYBOARD_MODIFIER_LEFTSHIFT + KEYBOARD_MODIFIER_LEFTGUI);
                flashButton(1);
                break;
            case 2:
                // Not Set
                break;
            case 3:
                // Not Set
                break;
            case 4:
                // Discord Toggle Deafen
                pressKey(HID_KEY_D, KEYBOARD_MODIFIER_LEFTCTRL + KEYBOARD_MODIFIER_LEFTSHIFT + KEYBOARD_MODIFIER_LEFTALT + KEYBOARD_MODIFIER_LEFTGUI);
                discordStates.isDeafened = !discordStates.isDeafened;
                discordStates.isMuted = discordStates.isDeafened || discordStates.wasMutedBeforeDeafened;
                break;
            case 5:
                // Full Screen Screenshot
                pressKey(HID_KEY_3, KEYBOARD_MODIFIER_LEFTSHIFT + KEYBOARD_MODIFIER_LEFTGUI);
                flashButton(5);
                break;
            case 6:
                // Not Set
                break;
            case 7:
                // Not Set
                break;
            case 8:
                // Not Set
                break;
            case 9:
                // Touch Bar Screenshot
                pressKey(HID_KEY_5, KEYBOARD_MODIFIER_LEFTSHIFT + KEYBOARD_MODIFIER_LEFTGUI);
                flashButton(9);
                break;
            case 10:
                // Not Set
                break;
            case 11:
                // Not Set
                break;
            case 12:
                // Mode 0
                mode = 0;
                break;
            case 13:
                // Mode 1
                mode = 1;
                break;
            case 14:
                // Mode 2
                mode = 2;
                break;
            case 15:
                // Mode 3
                mode = 3;
                break;
            }
            break;
        case 1:
            switch (button)
            {
            case 0:
                // Not Set
                break;
            case 1:
                // Not Set
                break;
            case 2:
                // Not Set
                break;
            case 3:
                // Not Set
                break;
            case 4:
                // Not Set
                break;
            case 5:
                // Not Set
                break;
            case 6:
                // Not Set
                break;
            case 7:
                // Not Set
                break;
            case 8:
                // Not Set
                break;
            case 9:
                // Not Set
                break;
            case 10:
                // Not Set
                break;
            case 11:
                // Not Set
                break;
            case 12:
                // Mode 0
                mode = 0;
                break;
            case 13:
                // Mode 1
                mode = 1;
                break;
            case 14:
                // Mode 2
                mode = 2;
                break;
            case 15:
                // Mode 3
                mode = 3;
                break;
            }
            break;
        case 2:
            switch (button)
            {
            case 0:
                // Not Set
                break;
            case 1:
                // Not Set
                break;
            case 2:
                // Not Set
                break;
            case 3:
                // Not Set
                break;
            case 4:
                // Not Set
                break;
            case 5:
                // Not Set
                break;
            case 6:
                // Not Set
                break;
            case 7:
                // Not Set
                break;
            case 8:
                // Not Set
                break;
            case 9:
                // Not Set
                break;
            case 10:
                // Not Set
                break;
            case 11:
                // Not Set
                break;
            case 12:
                // Mode 0
                mode = 0;
                break;
            case 13:
                // Mode 1
                mode = 1;
                break;
            case 14:
                // Mode 2
                mode = 2;
                break;
            case 15:
                // Mode 3
                mode = 3;
                break;
            }
            break;
        case 3:
            switch (button)
            {
            case 0:
                // Not Set
                break;
            case 1:
                // Not Set
                break;
            case 2:
                // Not Set
                break;
            case 3:
                // Not Set
                break;
            case 4:
                // Not Set
                break;
            case 5:
                // Not Set
                break;
            case 6:
                // Not Set
                break;
            case 7:
                // Not Set
                break;
            case 8:
                // Not Set
                break;
            case 9:
                // Not Set
                break;
            case 10:
                // Not Set
                break;
            case 11:
                // Not Set
                break;
            case 12:
                // Mode 0
                mode = 0;
                break;
            case 13:
                // Mode 1
                mode = 1;
                break;
            case 14:
                // Mode 2
                mode = 2;
                break;
            case 15:
                // Mode 3
                mode = 3;
                break;
            }
            break;
        }
        // animate(button);
        resetColours();
    }
};