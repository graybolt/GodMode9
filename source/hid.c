#include "hid.h"
#include "timer.h"

u32 InputWait() {
    u32 pad_state_old = HID_STATE;
    timer_start();
    while (true) {
        u32 pad_state = HID_STATE;
        if (!(~pad_state & BUTTON_ANY)) { // no buttons pressed
            pad_state_old = pad_state;
            continue;
        }
        if ((pad_state == pad_state_old) && (!(pad_state & BUTTON_ARROW) || timer_msec() < 120))
            continue;
        //Make sure the key is pressed
        u32 t_pressed = 0;
        for(; (t_pressed < 0x13000) && (pad_state == HID_STATE); t_pressed++);
        if (t_pressed >= 0x13000)
            return ~pad_state;
    }
}
