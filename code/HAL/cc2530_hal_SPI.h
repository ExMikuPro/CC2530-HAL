#include "cc2530_hal_GPIO.h"
#include "stdint.h"
#include "ioCC2530.h"
#ifndef CC2530_HAL_SPI_H
#define CC2530_HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
  
typedef uint8_t  uint8;
typedef uint16_t uint16;

#define SPI_GPIO_OUTPUT(port,pin) GPIO_Mode_Output(port,pin) // SPI输入
#define SPI_GPIO_INPUT(port,pin) GPIO_Mode_Input(port,pin)   // SPI输出
#define SPI_GPIO_SET(port,pin) GPIO_GPIO_SET(port, pin)      // SPI置位
#define SPI_GPIO_RESET(port,pin) GPIO_GPIO_RESET(port, pin)  // SPI复位
#define SPI_GPIO_GET(port,pin) GPIO_IO_GET(port,pin)         // 获取SPI

// 复用
#define HW_SPI1_ALT2        3 // SCK:P1_5, MISO:P1_6, MOSI:P1_7

// 传送位顺序
#define HW_SPI_BITORDER_MSB 0  // MSB
#define HW_SPI_BITORDER_LSB 1  // LSB

// SPI 时钟极性
#define HW_SPI_CPOL_LOW     0  // 负时钟极性
#define HW_SPI_CPOL_HIGH    1  // 正时钟极性

// SPI 时钟相位
#define HW_SPI_CPHA_FIRST   0
#define HW_SPI_CPHA_SECOND  1
  
// 初始化SPI CS端口
#define SPI_INIT_CS(port,pin) do{\
    SPI_GPIO_OUTPUT(port,pin);\
    SPI_GPIO_SET(port,pin);\
}while(0)

#define SPI_CS_SELECT(CS_Port, CS_Pin)  SPI_GPIO_RESET(CS_Port, CS_Pin) // 选择设备
#define SPI_CS_RELEASE(CS_Port, CS_Pin) SPI_GPIO_SET(CS_Port, CS_Pin)   // 释放设备

// 软件 SPI 处理

#define SW_SPI_TX 0
#define SW_SPI_RX 1



  
typedef struct
{    
    uint8 alternate;
    uint8 bitOrder;
    uint8 CPOL, CPHA;
} HwSPIConfig_t; 



void SPI_Init_HW(HwSPIConfig_t *hw);

static void SPI_Init_SPI1(uint8 alternate,uint8 bitOrder, uint8 CPOL, uint8 CPHA);


int SPI_Send_Byte(uint8 alternate, uint8 byte);

uint8 SPI_Read_Byte(uint8 alternate);

static void SPI_Init_SPI1(uint8 alternate,uint8 bitOrder, uint8 CPOL, uint8 CPHA);

static int HWSPI_Send_Byte(uint8 byte);

static uint8 HWSPI_Read_Byte(void);
  
  
#ifdef __cplusplus
}
#endif

#endif