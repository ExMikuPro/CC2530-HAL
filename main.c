#include "ioCC2530.h"
#include "cc2530_hal.h"
#include <stdio.h>
#include <stdint.h>


void main()
{
    CLOCK_SET_SYSTEM_32MHZ(); // 配置系统时钟
    GPIO_IO_OUTPUT(0,4); // 配置为通用接口
    GPIO_GPIO_RESET(0, 4); // 将LED端口复位
    GPIO_IO_INPUT(0,1,GPIO_INPUT_TRISTATE);
    /* 无限循环 */
    while(1){
      if(P0_1 == 0){
        GPIO_GPIO_SET(0, 4); // 将LED端口置位
      }else{
        HAL_delay(SYSCLK_32MHZ,1000); // 延迟1秒执行
        GPIO_GPIO_RESET(0, 4); // 将LED端口复位
        while(P0_1 != 0);
      }
    }
}


