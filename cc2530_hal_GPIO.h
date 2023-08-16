#ifndef CC2530_IOCTL_H
#define CC2530_IOCTL_H

#ifdef __cplusplus
extern "C" {
#endif

/* GPIO ״̬ */
#define GPIO_OUTPUT          0 // ���
#define GPIO_INPUT_PULLUP    1 // ��������
#define GPIO_INPUT_PULLDOWN  2 // ��������
#define GPIO_INPUT_TRISTATE  3 // ������̬

#define GPIO_SET 1     // ��λ
#define GPIO_RESET 0   // ��λ

#define GPIO_GPIO_SET(port, pin)      P##port##_##pin = GPIO_SET // ��λ
#define GPIO_GPIO_RESET(port, pin)    P##port##_##pin = GPIO_RESET // ��λ
#define GPIO_GET(port, pin)           P##port##_##pin // ��ȡ״̬


#define GPIO_IOCTL_BV(x)      (1<<(x))   // λ����

// GPIOͨ��ģʽ
#define GPIO_Type_TY(port,pin) do{\
  P##port##SEL &= ~GPIO_IOCTL_BV(pin);\
}while(0)
  
// GPIO����ģʽ
#define GPIO_Type_WS(port,pin) do{\
P##port##SEL |= GPIO_IOCTL_BV(pin);\
} while(0)
  
// GPIO����ģʽ
#define GPIO_Mode_Input(port,pin) do{\
P##port##DIR &= ~GPIO_IOCTL_BV(pin);\
} while(0)

// GPIO���ģʽ
#define GPIO_Mode_Output(port,pin) do{\
P##port##DIR |= GPIO_IOCTL_BV(pin);\
} while(0)
    
// GPIO����״̬
#define GPIO_Input_Mode(port,pin,var) do{\
if(var == 0){\
  P##port##INP &= ~GPIO_IOCTL_BV(pin);\
}else{\
  P##port##INP |= GPIO_IOCTL_BV(pin);\
}\
} while(0)

// GPIO��������
// P1_0, P1_1 ������������
#define GPIO_IO_INPUT(port, pin, mode) do {\
    if (port > 2 || pin > 7) {break;}\
    if ((port) == 1 && ((pin) == 0 || (pin) == 1)){ break; }\
    GPIO_Type_TY(port,pin);\
    GPIO_Mode_Input(port,pin);\
    if (mode == GPIO_INPUT_TRISTATE){\
        GPIO_Input_Mode(port , pin , 1);\
    }else {\
        GPIO_Input_Mode(port , pin , 0);\
        if (mode == GPIO_INPUT_PULLUP) GPIO_Input_Mode(2 , (5+port), 0);\
        else GPIO_Input_Mode(2 , (5+port), 1);\
    }\
} while(0)
 
#ifdef __cplusplus
}
#endif

#endif /* #ifndef CC2530_IOCTL_H */
