#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define I2C_DRIVER I2CD0

// We switch pins GP4 and GP5 to the mode of operation with the I2C0 block
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5
#define I2C1_CLOCK_SPEED 100000

// Display settings
#define OLED_DISPLAY_ADDRESS 0x3C

// We use the built-in ready-made preset for 64x32 screens
#define OLED_DISPLAY_64X32

// Hardware memory offset (protection against garbage and noise on SSD1306)
#define OLED_COLUMN_OFFSET 32

#define OLED_BRIGHTNESS 128
