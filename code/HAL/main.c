#include "ioCC2530.h"
#include "cc2530_hal.h"
#include <stdio.h>
#include <stdint.h>

#define CS_Port 2
#define CS_Pin 0

#define DC_Port 1
#define DC_Pin 4

#define RST_Port 1
#define RST_Pin 0

void sendCMD(uint8 cmd);
void sendDATA(uint8 data);
void displayInit(void);
void displayClear(void);


void sendCMD(uint8 cmd){ // 发送命令
  SPI_CS_SELECT(CS_Port, CS_Pin);
  SPI_GPIO_RESET(DC_Port,DC_Pin);
  SPI_Send_Byte(HW_SPI1_ALT2,cmd); // 使用硬件SPI的情况下
  SPI_CS_RELEASE(CS_Port, CS_Pin);
}

void sendDATA(uint8 data){ // 发送数据
  SPI_CS_SELECT(CS_Port, CS_Pin);
  SPI_GPIO_SET(DC_Port,DC_Pin);
  SPI_Send_Byte(HW_SPI1_ALT2,data); // 使用硬件SPI的情况下
  SPI_CS_RELEASE(CS_Port, CS_Pin);
}

void displayInit(void){
  // 硬件 SPI 初始化
  HwSPIConfig_t cfg = {
    .alternate = HW_SPI1_ALT2,
    .bitOrder  = HW_SPI_BITORDER_MSB,
    .CPOL      = HW_SPI_CPOL_HIGH,
    .CPHA      = HW_SPI_CPHA_SECOND,
  };
  
  // 初始化SPI
  SPI_Init_HW(&cfg);
  
  // 配置CS,DC,RST端口
  SPI_INIT_CS(CS_Port,CS_Pin);
  SPI_GPIO_OUTPUT(DC_Port,DC_Pin);
  SPI_GPIO_OUTPUT(RST_Port,RST_Pin);
}

void displayClear(void){ // 清空屏幕
  uint8 page , x;
  for(page = 0; page < 8; page++){
    sendCMD(0xb0 + page);
    sendCMD(0x01);
    sendCMD(0x10);
    for (x = 0; x < 128; x++){
      sendDATA(0xFF);
    }
  }
}

void main()
{
  // 设置系统运行速度
  CLOCK_SET_SYSTEM_32MHZ();
  
  displayInit();
  
  // 重置屏幕
  SPI_GPIO_RESET(RST_Port,RST_Pin);
  HAL_Delay(SYSCLK_32MHZ,60);
  SPI_GPIO_SET(RST_Port,RST_Pin);
  
  // 发送初始化屏幕命令
  
  sendCMD(0xae);
  sendCMD(0x00);
  sendCMD(0x10);
  sendCMD(0x40);
  sendCMD(0x81);
  sendCMD(0xcf);
  sendCMD(0xa1);    
  sendCMD(0xc8); 
  sendCMD(0xa6);
  sendCMD(0xa8);
  sendCMD(0x3f);
  sendCMD(0xd3);
  sendCMD(0x00);
  sendCMD(0xd5);
  sendCMD(0x80);
  sendCMD(0xd9);
  sendCMD(0xf1);
  sendCMD(0xda);
  sendCMD(0x12);
  sendCMD(0xdb);
  sendCMD(0x40);
  sendCMD(0x20);
  sendCMD(0x02);
  sendCMD(0x8d);
  sendCMD(0x14);
  sendCMD(0xa4);
  sendCMD(0xa6);
  sendCMD(0xaf);
  
  displayClear();  // 清除屏幕
  
  while(1);
  
}