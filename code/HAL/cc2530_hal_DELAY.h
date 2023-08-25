#ifndef CC2530_HAL_DELAY_H
#define CC2530_HAL_DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
  
#define SYSCLK_16MHZ 0
#define SYSCLK_32MHZ 1
  
  void HAL_Delay(int sysClk , uint16_t Ms);
  
  void HAL_Delay(int sysClk, uint16_t nMs)
  {
    uint16_t i, j;
    uint16_t loop1Ms;
  
    if (sysClk == SYSCLK_16MHZ){
      loop1Ms = 535;
    }else{
      loop1Ms = 1070;
    }

    for(i = 0; i < nMs; i++) for(j = 0; j < loop1Ms; j++);
  }
  
  
#ifdef __cplusplus
}
#endif

#endif