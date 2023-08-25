#include "cc2530_hal_SPI.h"


// 硬件SPI处理函数

void SPI_Init_HW(HwSPIConfig_t *hw){
  switch(hw->alternate){
  case HW_SPI1_ALT2:
    SPI_Init_SPI1(HW_SPI1_ALT2, hw->bitOrder, hw->CPOL, hw->CPHA);
  break;
    
  default:
  break;
  }
}

// SPI 发送数据
int SPI_Send_Byte(uint8 alternate, uint8 byte)
{
    int ret = -1;
    
    if (alternate == HW_SPI1_ALT2) ret = HWSPI_Send_Byte(byte);
    
    return ret;
}

// SPI 接收数据
uint8 SPI_Read_Byte(uint8 alternate)
{
    uint8 byte = 0x00;

    if (alternate == HW_SPI1_ALT2) byte = HWSPI_Read_Byte();

    return byte;
}


// 初始化SPI
static void SPI_Init_SPI1(uint8 alternate,uint8 bitOrder, uint8 CPOL, uint8 CPHA){
  U1CSR = 0x0;
  U1GCR |= 0x11;
  
  U1GCR |= 0x11;
  U1BAUD = 0x00;
  
  if(alternate == HW_SPI1_ALT2){
    // 设置备用位置2 SCK:P1_5, MOSI:P1_6, MISO:P1_7
    PERCFG |= 0x02;
    
    // 配置P1三个端口为外设
    P1SEL |= 0xE0;
    
  }
    
  // 设置传送位顺序
  if (bitOrder == HW_SPI_BITORDER_MSB){
    // 设置传送位顺序为 MSB
    U1GCR |= (1 << 5); 
  }else{
    // 设置传送位顺序为 LSB
    U1GCR &= ~(1 << 5);
  }
  
  // 设置SPI时钟极性
  if (CPOL == HW_SPI_CPOL_HIGH){
    // 正时钟极性
    U1GCR |= (1<<7);
  }else{
    // 负时钟极性
    U1GCR &= ~(1<<7);
  }
  
  // 设置SPI时钟相位
  if (CPHA == HW_SPI_CPHA_FIRST){
    U1GCR &= ~(1<<6);
  }else{
    U1GCR |= (1<<6);
  }
  
  // 设置优先级控制为USART1
  P2SEL &= ~0x20;
  
  // 启用已配置的SPI
  U1CSR |= 0x40;
}

// 通过硬件SPI1发送一个字节
static int HWSPI_Send_Byte(uint8 byte)
{
    uint16 timeout = 6420;  // 设置超时时间
    
    
    U1CSR &= ~0x02; 
    // 将数据写入缓存区
    U1DBUF = byte;
    
    // 判断是否将缓存区数据发送完成
    while (!(U1CSR & 0x02)) if (--timeout == 0) break;
    
    // 发送成功返回0
    return (timeout == 0)? -1 : 0;
}

// 接受字节并返回
static uint8 HWSPI_Read_Byte(void)
{
    uint8 byte = U1DBUF;
    return byte;
}


