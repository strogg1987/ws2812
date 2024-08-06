#ifndef WS2812_H_
#define WS2812_H_

#include "stm32g0xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#endif /* WS2812_H_ */

#define DELAY_LEN 52
#define LED_COUNT 6
#define ARRAY_LEN DELAY_LEN + LED_COUNT * 24
#define HIGH 56
#define LOW 23
#define BitIsSet(reg, bit) ((reg & (1 << bit)) != 0)

void WS2812_Init(void);
void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel, uint8_t Gpixel, uint8_t Bpixel, uint16_t posX);
void ws2812_light(void);
void ws2812_setValue(void);
void ws2812_prepareValue(uint8_t r00, uint8_t g00, uint8_t b00,
                         uint8_t r01, uint8_t g01, uint8_t b01,
                         uint8_t r02, uint8_t g02, uint8_t b02,
                         uint8_t r03, uint8_t g03, uint8_t b03,
                         uint8_t r04, uint8_t g04, uint8_t b04,
                         uint8_t r05, uint8_t g05, uint8_t b05);
void delay_us(uint32_t us);
void ws2812_stop(void);
