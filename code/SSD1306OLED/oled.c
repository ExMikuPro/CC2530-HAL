#include "ioCC2530.h"
#include "cc2530_hal.h"
#include "dev_display.h"
#include <stdio.h>
#include <stdint.h>



void main()
{
  // 设置系统运行速度
  CLOCK_SET_SYSTEM_32MHZ();
  
  display_Init_SPI_HW();
  
  while(1);
  
}