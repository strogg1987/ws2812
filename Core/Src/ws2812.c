#include "ws2812.h"

//----------------------------------------------------------------------------

extern TIM_HandleTypeDef htim3;

//----------------------------------------------------------------------------

uint16_t BUF_DMA[ARRAY_LEN] = {0};
uint8_t rgb_temp[6][3];

void WS2812_Init(void)
{
    int i;
    for (i = DELAY_LEN; i < ARRAY_LEN; i++)
        BUF_DMA[i] = LOW;
}

void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel, uint8_t Gpixel, uint8_t Bpixel, uint16_t posX)
{
    volatile uint16_t i;
    for (i = 0; i < 8; i++)
    {
        if (BitIsSet(Rpixel, (7 - i)) == 1)
        {
            BUF_DMA[DELAY_LEN + posX * 24 + i + 8] = HIGH;
        }
        else
        {
            BUF_DMA[DELAY_LEN + posX * 24 + i + 8] = LOW;
        }
        if (BitIsSet(Gpixel, (7 - i)) == 1)
        {
            BUF_DMA[DELAY_LEN + posX * 24 + i + 0] = HIGH;
        }
        else
        {
            BUF_DMA[DELAY_LEN + posX * 24 + i + 0] = LOW;
        }

        if (BitIsSet(Bpixel, (7 - i)) == 1)
        {
            BUF_DMA[DELAY_LEN + posX * 24 + i + 16] = HIGH;
        }
        else
        {
            BUF_DMA[DELAY_LEN + posX * 24 + i + 16] = LOW;
        }
    }
}

void ws2812_prepareValue(uint8_t r00, uint8_t g00, uint8_t b00,
                         uint8_t r01, uint8_t g01, uint8_t b01,
                         uint8_t r02, uint8_t g02, uint8_t b02,
                         uint8_t r03, uint8_t g03, uint8_t b03,
                         uint8_t r04, uint8_t g04, uint8_t b04,
                         uint8_t r05, uint8_t g05, uint8_t b05)

{

    rgb_temp[0][0] = r00;
    rgb_temp[0][1] = g00;
    rgb_temp[0][2] = b00;

    rgb_temp[1][0] = r01;
    rgb_temp[1][1] = g01;
    rgb_temp[1][2] = b01;

    rgb_temp[2][0] = r02;
    rgb_temp[2][1] = g02;
    rgb_temp[2][2] = b02;

    rgb_temp[3][0] = r03;
    rgb_temp[3][1] = g03;
    rgb_temp[3][2] = b03;

    rgb_temp[4][0] = r04;
    rgb_temp[4][1] = g04;
    rgb_temp[4][2] = b04;

    rgb_temp[5][0] = r05;
    rgb_temp[5][1] = g05;
    rgb_temp[5][2] = b05;
}

void ws2812_setValue(void)
{
    uint8_t n = 0;
    for (n = 0; n < 12; n++)
    {
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[0][0], rgb_temp[0][1], rgb_temp[0][2], n * 12);
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[1][0], rgb_temp[1][1], rgb_temp[1][2], n * 12 + 1);
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[2][0], rgb_temp[2][1], rgb_temp[2][2], n * 12 + 2);
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[3][0], rgb_temp[3][1], rgb_temp[3][2], n * 12 + 3);
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[4][0], rgb_temp[4][1], rgb_temp[4][2], n * 12 + 4);
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[5][0], rgb_temp[5][1], rgb_temp[5][2], n * 12 + 5);
    }
}

void ws2812_light(void)
{
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, (uint32_t *)&BUF_DMA, ARRAY_LEN);
}

void ws2812_stop(void)
{
    HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_2);
}
void delay_us(uint32_t us)
{
    // Assuming the CPU frequency is 64 MHz
    const uint32_t cycles_per_us = 64; // Number of cycles per microsecond
    uint32_t cycles = cycles_per_us * us;

    // A simple loop to add delay
    while (cycles--)
    {
        __asm("nop"); // NOP (No Operation) Assembly Instruction
    }
}