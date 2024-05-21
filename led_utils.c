#include "led_utils.h"

void light_up_led(unsigned char* mem_base, unsigned short color, int led_num) {
    // Extract the RGB components from the color
    uint8_t r = (color >> 11) & 0x1F;  // Red: bits 11-15
    uint8_t g = (color >> 5) & 0x3F;   // Green: bits 5-10
    uint8_t b = color & 0x1F;          // Blue: bits 0-4

    // Scale from 5/6 bit color to 8 bit color
    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    // Create the 24-bit RGB value
    uint32_t rgb = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;

    // Determine the offset for the LED register
    uint32_t offset = (led_num == 1) ? SPILED_REG_LED_RGB1_o : SPILED_REG_LED_RGB2_o;

    // Write the RGB value to the LED register
    *((volatile uint32_t*)(mem_base + offset)) = rgb;
}

void turn_off_led(unsigned char* mem_base, int led_num) {
    // Determine the offset for the LED register
    uint32_t offset = (led_num == 1) ? SPILED_REG_LED_RGB1_o : SPILED_REG_LED_RGB2_o;

    // Turn off the LED
    *((volatile uint32_t*)(mem_base + offset)) = 0;
}

void flicker_led(unsigned char* mem_base, unsigned short color, int led_num) {
  light_up_led(mem_base, color, led_num);
  usleep(15000);
  turn_off_led(mem_base, led_num);
}

void update_led(unsigned char* mem_base, int snake1_len, int snake2_len) {
    if(!(snake1_len) && !(snake2_len)) return;  
    // Calculate the LED pattern for each snake
    uint32_t led_pattern_snake1 = snake1_len > 0 ? ((1 << (snake1_len % LED_RESET)) - 1) : 0;
    uint32_t led_pattern_snake2 = snake2_len > 0 ? (0xFFFFFFFF << (32 - (snake2_len % LED_RESET))) : 0xFFFFFFFF;

    // Update the LED line register with the new pattern
    *((volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o)) = led_pattern_snake1 | led_pattern_snake2;
}
