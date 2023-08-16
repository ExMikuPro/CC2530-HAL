#include "ioCC2530.h"
#include "cc2530_hal.h"
#include <stdio.h>

void main()
{
    /* 在 Terminal IO（控制台） 中输出提示信息 */
  
    GPIO_IO_OUTPUT(0,4); // 配置为通用接口
    GPIO_GPIO_RESET(0, 4); // 将LED端口复位
    GPIO_IO_INPUT(0,1,GPIO_INPUT_TRISTATE);
    /* 无限循环 */
    while(1){
      if(P0_1 == 0){
        GPIO_GPIO_SET(0, 4); // 将LED端口置位
      }else{
        GPIO_GPIO_RESET(0, 4); // 将LED端口复位
        while(P0_1 != 0);
      }
    }
}
