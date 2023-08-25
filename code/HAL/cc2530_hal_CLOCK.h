#ifndef CC2530_HAL_CLOCK_H
#define CC2530_HAL_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

// 使用外部时钟
// 设置系统运行时钟速度
#define CLOCK_SET_SYSTEM_32MHZ() do{\
  CLKCONCMD &= ~0x40;\
  while(CLKCONSTA & 0x40);\
  CLKCONCMD &= ~0x47;\
}while(0)

#define CLOCK_SET_SYSTEM_16MHZ() do{\
  CLKCONCMD &= ~0x40;\
  while(CLKCONSTA & 0x40);\
  CLKCONCMD &= ~0xF6;\
}while(0)

#ifdef __cplusplus
}
#endif

#endif