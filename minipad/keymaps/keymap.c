#include QMK_KEYBOARD_H

// 1. KEYBOARD LAYOUT (HERE WE USE UP AND SPACE)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_UP, KC_SPC
    )
};

// 2. CPS BAR SETUP 
#define NUM_SLOTS 10  // We divide 1 second into 10 slots of 100 ms

uint16_t click_slots[NUM_SLOTS] = {0}; // An array for storing clicks on time slots
uint8_t  current_slot = 0;             // The current active time slot
uint32_t slot_timer = 0;               // Timer for counting 100 ms
uint16_t current_cps = 0;              // Current CPS value for output

// Interception of keystrokes for instant counting
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        click_slots[current_slot]++; // Add a click to the current 100-ms slot
    }
    return true;
}

// 3. DISPLAY LOGIC ON OLED SCREENS
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_on();
    return rotation;
}

bool oled_task_user(void) {
    // Fast timer: we move the time window every 100 milliseconds
    if (timer_elapsed32(slot_timer) >= 100) {
        slot_timer = timer_read32();
        
        // Let's go to the next time slot
        current_slot = (current_slot + 1) % NUM_SLOTS;
        click_slots[current_slot] = 0; // We erase old clicks from this slot

        // We count the sum of clicks in all 10 slots for the last second
        uint16_t total_clicks = 0;
        for (uint8_t i = 0; i < NUM_SLOTS; i++) {
            total_clicks += click_slots[i];
        }
        
        // We update the value of CPS
        current_cps = total_clicks;
        
        // Forcefully clear the screen for smooth rendering
        oled_clear(); 
    }

    // Hard limited to 99 CPS
    if (current_cps > 99) {
        current_cps = 99;
    }

    // OUTPUT TEXT IN THE CENTER (Line 1)
    uint8_t text_column = (current_cps < 10) ? 2 : 1;
    oled_set_cursor(text_column, 1);
    oled_write_P(PSTR("CPS: "), false);

    if (current_cps >= 10) {
        oled_write_char('0' + (current_cps / 10), false);
        oled_write_char('0' + (current_cps % 10), false);
    } else {
        oled_write_char('0' + current_cps, false);
    }

    // CONCLUSION OF FAT DOUBLE SCALE (Lines 2 and 3)
    uint8_t bar_length = current_cps / 2;
    if (bar_length > 10) bar_length = 10;

    // The upper layer of the scale (Line 2)
    oled_set_cursor(0, 2);
    for (uint8_t i = 0; i < 10; i++) {
        if (i < bar_length) {
            oled_write_char('#', false);
        } else {
            oled_write_char('.', false);
        }
    }

    // The bottom layer of the scale (Line 3)
    oled_set_cursor(0, 3);
    for (uint8_t i = 0; i < 10; i++) {
        if (i < bar_length) {
            oled_write_char('#', false);
        } else {
            oled_write_char('.', false);
        }
    }

    return false;
}
#endif
