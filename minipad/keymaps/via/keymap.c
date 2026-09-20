#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_UP, KC_SPC
    ),

    [1] = LAYOUT(
        KC_LEFT, KC_RIGHT
    ),

    [2] = LAYOUT(
        KC_DOWN, KC_ENTER
    ),

    [3] = LAYOUT(
        KC_ESC, KC_TAB
    )
};

// CPS BAR SETUP
#define NUM_SLOTS 10

uint16_t click_slots[NUM_SLOTS] = {0};
uint8_t current_slot = 0;
uint32_t slot_timer = 0;
uint16_t current_cps = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        click_slots[current_slot]++;
    }

    return true;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_on();
    return rotation;
}

bool oled_task_user(void) {
    if (timer_elapsed32(slot_timer) >= 100) {
        slot_timer = timer_read32();

        current_slot = (current_slot + 1) % NUM_SLOTS;
        click_slots[current_slot] = 0;

        uint16_t total_clicks = 0;

        for (uint8_t i = 0; i < NUM_SLOTS; i++) {
            total_clicks += click_slots[i];
        }

        current_cps = total_clicks;

        oled_clear();
    }

    if (current_cps > 99) {
        current_cps = 99;
    }

    uint8_t text_column = (current_cps < 10) ? 2 : 1;

    oled_set_cursor(text_column, 1);
    oled_write_P(PSTR("CPS: "), false);

    if (current_cps >= 10) {
        oled_write_char('0' + (current_cps / 10), false);
        oled_write_char('0' + (current_cps % 10), false);
    } else {
        oled_write_char('0' + current_cps, false);
    }

    uint8_t bar_length = current_cps / 2;

    if (bar_length > 10) {
        bar_length = 10;
    }

    oled_set_cursor(0, 2);

    for (uint8_t i = 0; i < 10; i++) {
        if (i < bar_length) {
            oled_write_char('#', false);
        } else {
            oled_write_char('.', false);
        }
    }

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
