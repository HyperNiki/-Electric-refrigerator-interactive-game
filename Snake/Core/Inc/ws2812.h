#ifndef WS2812_H_
#define WS2812_H_
//--------------------------------------------------
//#include "stm32f1xx_hal.h"
//#include <string.h>
//#include <stdlib.h>
//#include <stdint.h>
#include "main.h"
//--------------------------------------------------

#define DELAY_LEN 144
#define LED_COUNT 60
#define ARRAY_LEN DELAY_LEN + LED_COUNT*24
#define HIGH 65
#define LOW 26
//--------------------------------------------------
#define BitIsSet(reg, bit) ((reg & (1<<bit)) != 0)
//--------------------------------------------------
void ws2812_init(void);
void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel , uint8_t Gpixel, uint8_t Bpixel, uint16_t posX);
void ws2812_prepareValue (uint8_t r00, uint8_t g00, uint8_t b00,
    uint8_t r01, uint8_t g01, uint8_t b01,
    uint8_t r02, uint8_t g02, uint8_t b02,
    uint8_t r03, uint8_t g03, uint8_t b03);
void ws2812_setValue(void);
void ws2812_light(void);
void ws2812_test01(void);
void ws2812_test02(void);
void ws2812_test03(void);
void ws2812_test04(void);

void ws2812_fill(int R,int G,int B);
//--------------------------------------------------
#endif /* WS2812_H_ */
