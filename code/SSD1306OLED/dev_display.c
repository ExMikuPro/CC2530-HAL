#include "dev_display.h"


void displayInit_SPI_HW(void){
  // Ӳ�� SPI ��ʼ��
  HwSPIConfig_t cfg = {
    .alternate = HW_SPI1_ALT2,
    .bitOrder  = HW_SPI_BITORDER_MSB,
    .CPOL      = HW_SPI_CPOL_HIGH,
    .CPHA      = HW_SPI_CPHA_SECOND,
  };
  
  // ��ʼ��SPI
  SPI_Init_HW(&cfg);
  
  // ����CS,DC,RST�˿�
  SPI_INIT_CS(CS_Port,CS_Pin);
  SPI_GPIO_OUTPUT(DC_Port,DC_Pin);
  SPI_GPIO_OUTPUT(RST_Port,RST_Pin);
}

void sendCMD(uint8 cmd){ // ��������
  SPI_CS_SELECT(CS_Port, CS_Pin);
  SPI_GPIO_RESET(DC_Port,DC_Pin);
  SPI_Send_Byte(HW_SPI1_ALT2,cmd); // ʹ��Ӳ��SPI�������
  SPI_CS_RELEASE(CS_Port, CS_Pin);
}

void sendDATA(uint8 data){ // ��������
  SPI_CS_SELECT(CS_Port, CS_Pin);
  SPI_GPIO_SET(DC_Port,DC_Pin);
  SPI_Send_Byte(HW_SPI1_ALT2,data); // ʹ��Ӳ��SPI�������
  SPI_CS_RELEASE(CS_Port, CS_Pin);
}