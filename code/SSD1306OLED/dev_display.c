#include "dev_display.h"


void displayInit_SPI_HW(void){
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