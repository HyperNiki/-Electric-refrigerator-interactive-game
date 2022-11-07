#include "ws2812.h"
//----------------------------------------------------------------------------
extern TIM_HandleTypeDef htim2;
//----------------------------------------------------------------------------
uint16_t BUF_DMA_1 [ARRAY_LEN] = {0};
uint16_t BUF_DMA_2 [ARRAY_LEN] = {0};
uint8_t rgb_temp[12][3];
uint16_t DMA_BUF_TEMP[24];
//------------------------------------------------------------------
void ws2812_init(void)
{
  int i;
  for(i=DELAY_LEN;i<ARRAY_LEN;i++) BUF_DMA_1[i] = LOW;
  for(i=DELAY_LEN;i<ARRAY_LEN;i++) BUF_DMA_2[i] = LOW;
}
//------------------------------------------------------------------
void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel , uint8_t Gpixel, uint8_t Bpixel, uint16_t posX)
{
  volatile uint16_t i;
  for(i=0;i<8;i++)
  {
    if (BitIsSet(Rpixel,(7-i)) == 1)
    {
    	BUF_DMA_1[DELAY_LEN+posX*24+i+8] = HIGH;
    }else
    {
    	BUF_DMA_1[DELAY_LEN+posX*24+i+8] = LOW;
    }
    if (BitIsSet(Gpixel,(7-i)) == 1)
    {
    	BUF_DMA_1[DELAY_LEN+posX*24+i+0] = HIGH;
    }else
    {
    	BUF_DMA_1[DELAY_LEN+posX*24+i+0] = LOW;
    }
    if (BitIsSet(Bpixel,(7-i)) == 1)
    {
    	BUF_DMA_1[DELAY_LEN+posX*24+i+16] = HIGH;
    }else
    {
    	BUF_DMA_1[DELAY_LEN+posX*24+i+16] = LOW;
    }
  }
}
//------------------------------------------------------------------
void ws2812_prepareValue (uint8_t r00, uint8_t g00, uint8_t b00,
    uint8_t r01, uint8_t g01, uint8_t b01,
    uint8_t r02, uint8_t g02, uint8_t b02,
    uint8_t r03, uint8_t g03, uint8_t b03)
  {
  rgb_temp[0][0]=r00; rgb_temp[0][1]=g00; rgb_temp[0][2]=b00;
  rgb_temp[1][0]=r01; rgb_temp[1][1]=g01; rgb_temp[1][2]=b01;
  rgb_temp[2][0]=r02; rgb_temp[2][1]=g02; rgb_temp[2][2]=b02;
  rgb_temp[3][0]=r03; rgb_temp[3][1]=g03; rgb_temp[3][2]=b03;
}
//------------------------------------------------------------------
void ws2812_setValue(void)
{
  uint8_t n=0;
  for(n=0;n < LED_COUNT / 4;n++)
  {
    ws2812_pixel_rgb_to_buf_dma( rgb_temp[0][0], rgb_temp[0][1], rgb_temp[0][2], n*12);
    ws2812_pixel_rgb_to_buf_dma( rgb_temp[1][0], rgb_temp[1][1], rgb_temp[1][2], n*12+1);
    ws2812_pixel_rgb_to_buf_dma( rgb_temp[2][0], rgb_temp[2][1], rgb_temp[2][2], n*12+2);
    ws2812_pixel_rgb_to_buf_dma( rgb_temp[3][0], rgb_temp[3][1], rgb_temp[3][2], n*12+3);
  }
}
//------------------------------------------------------------------
void ws2812_light(void)
{
  HAL_TIM_PWM_Start_DMA(&htim2,TIM_CHANNEL_2,(uint32_t*)&BUF_DMA_1,ARRAY_LEN);
  HAL_TIM_PWM_Start_DMA(&htim2,TIM_CHANNEL_2,(uint32_t*)&BUF_DMA_2,ARRAY_LEN);
}
//------------------------------------------------------------------
void ws2812_test01(void)
{
  uint8_t i,j;
  ws2812_prepareValue(128, 0, 0, 0, 128, 0, 0, 0, 128, 64, 64, 0);
  ws2812_setValue();
  for(j=0;j<50;j++)
  {
    memcpy((void*)DMA_BUF_TEMP,(void*)(BUF_DMA_1+LED_COUNT / 3),LED_COUNT / 3);
    for(i=0;i<LED_COUNT;i++)
    {
      memcpy((void*)(i*LED_COUNT / 6+BUF_DMA_1+LED_COUNT / 3),(void*)(i*LED_COUNT / 6+BUF_DMA_1+LED_COUNT / 2),LED_COUNT / 3);
    }
    memcpy((void*)(BUF_DMA_1+LED_COUNT / 3+ARRAY_LEN),(void*)DMA_BUF_TEMP,LED_COUNT / 3);
    ws2812_light();
    HAL_Delay(100);
  }
}
//----------------------------------------------------------------------------
void ws2812_test02(void)
{
  uint8_t i,j,jj;
  int k=0;
  for(jj=0;jj<10;jj++)
  {
    for(j=0;j<32;j++)
    {
      for(i=0;i<LED_COUNT;i++)
      {
        k=1000*(32-j)/32;
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[i%12][0]*k/1000,rgb_temp[i%12][1]*k/1000,rgb_temp[i%12][2]*k/1000,i);
      }
      ws2812_light();
      HAL_Delay(10);
    }
    for(j=0;j<32;j++)
    {
      for(i=0;i<LED_COUNT;i++)
      {
        k=1000*(j+1)/32;
        ws2812_pixel_rgb_to_buf_dma(rgb_temp[i%12][0]*k/1000,rgb_temp[i%12][1]*k/1000,rgb_temp[i%12][2]*k/1000,i);
      }
      ws2812_light();
      HAL_Delay(10);
    }
  }
}
//-----------------------------------------------------------------------------
void ws2812_test03(void)
{
  uint8_t i,j,jj;
  int k=0;
  for(jj=0;jj<10;jj++)
  {
    for(j=0;j<32;j++)
    {
      for(i=0;i<LED_COUNT;i++)
      {
        if((i<12)||((i>=24)&&(i<36))||((i>=48)&&(i<60))||((i>=72)&&(i<84))||((i>=96)&&(i<108))||((i>=120)&&(i<132)))
        {
          k=1000*(32-j)/32;
          ws2812_pixel_rgb_to_buf_dma(rgb_temp[i%12][0]*k/1000,rgb_temp[i%12][1]*k/1000,rgb_temp[i%12][2]*k/1000,i);
        }
        else
        {
          k=1000*(j+1)/32;
          ws2812_pixel_rgb_to_buf_dma(rgb_temp[i%12][0]*k/1000,rgb_temp[i%12][1]*k/1000,rgb_temp[i%12][2]*k/1000,i);
        }
      }
      ws2812_light();
      HAL_Delay(15);
    }
    for(j=0;j<32;j++)
    {
      for(i=0;i<LED_COUNT;i++)
      {
        if((i<12)||((i>=24)&&(i<36))||((i>=48)&&(i<60))||((i>=72)&&(i<84))||((i>=96)&&(i<108))||((i>=120)&&(i<132)))
        {
          k=1000*(j+1)/32;
          ws2812_pixel_rgb_to_buf_dma(rgb_temp[i%12][0]*k/1000,rgb_temp[i%12][1]*k/1000,rgb_temp[i%12][2]*k/1000,i);
        }
        else
        {
          k=1000*(32-j)/32;
          ws2812_pixel_rgb_to_buf_dma(rgb_temp[i%12][0]*k/1000,rgb_temp[i%12][1]*k/1000,rgb_temp[i%12][2]*k/1000,i);
        }
      }
      ws2812_light();
      HAL_Delay(15);
    }
  }
}
//----------------------------------------------------------------------------
void ws2812_test04(void)
{
  uint8_t i,j,jj;
  int k=0;
  for(jj=0;jj<40;jj++)
  {
    for(j=0;j<32;j++)
    {
      for(i=0;i<LED_COUNT;i++)
      {
        if(j<16) k=1000*(j)/16;
        else k=1000*(32-j)/16;
        if(i%12==0) ws2812_pixel_rgb_to_buf_dma(128*k/1000,128*(1000-k)/1000,0,i);
        if(i%12==1) ws2812_pixel_rgb_to_buf_dma(0,128*k/1000,128*(1000-k)/1000,i);
        if(i%12==2) ws2812_pixel_rgb_to_buf_dma(128*k/1000,0,128*(1000-k)/1000,i);
        if(i%12==3) ws2812_pixel_rgb_to_buf_dma(128*(1000-k)/1000,128*k/2000,128*k/2000,i);
        if(i%12==4) ws2812_pixel_rgb_to_buf_dma(128*k/2000,128*k/2000,128*(1000-k)/1000,i);
        if(i%12==5) ws2812_pixel_rgb_to_buf_dma(128*k/2000,128*(1000-k)/1000,128*k/2000,i);
        if(i%12==6) ws2812_pixel_rgb_to_buf_dma(128*(1000-k)/2000,128*(1000-k)/2000,128*k/1000,i);
        if(i%12==7) ws2812_pixel_rgb_to_buf_dma(128*k/1000,128*(1000-k)/2000,128*(1000-k)/2000,i);
        if(i%12==8) ws2812_pixel_rgb_to_buf_dma(128*(1000-k)/2000,128*k/1000,128*(1000-k)/2000,i);
        if(i%12==9) ws2812_pixel_rgb_to_buf_dma(128*(1000-k)/3000,128*(1000-k)/667,128*k/1000,i);
        if(i%12==10) ws2812_pixel_rgb_to_buf_dma(128*k/3000,128*(1000-k)/667,128*(1000-k)/1000,i);
        if(i%12==11) ws2812_pixel_rgb_to_buf_dma(128*(1000-k)/3000,128*k/667,128*(1000-k)/3000,i);
      }
      ws2812_light();
      HAL_Delay(20);
    }
  }
}
//----------------------------------------------------------------------------
