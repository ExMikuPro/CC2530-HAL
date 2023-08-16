#ifndef CC2530_IOCTL_H
#define CC2530_IOCTL_H

#ifdef __cplusplus
extern "C" {
#endif

/* GPIO 状态 */
#define GPIO_OUTPUT          0 // 输出
#define GPIO_INPUT_PULLUP    1 // 输入上拉
#define GPIO_INPUT_PULLDOWN  2 // 输入下拉
#define GPIO_INPUT_TRISTATE  3 // 输入三态

#define GPIO_SET 1     // 置位
#define GPIO_RESET 0   // 复位

#define GPIO_GPIO_SET(port, pin)      P##port##_##pin = GPIO_SET // 置位
#define GPIO_GPIO_RESET(port, pin)    P##port##_##pin = GPIO_RESET // 复位
#define GPIO_GET(port, pin)           P##port##_##pin // 获取状态


#define GPIO_IOCTL_BV(x)      (1<<(x))   // 位左移

// GPIO通用模式
#define GPIO_Type_TY(port,pin) do{\
  P##port##SEL &= ~GPIO_IOCTL_BV(pin);\
}while(0)
  
// GPIO外设模式
#define GPIO_Type_WS(port,pin) do{\
P##port##SEL |= GPIO_IOCTL_BV(pin);\
} while(0)
  
// GPIO输入模式
#define GPIO_Mode_Input(port,pin) do{\
P##port##DIR &= ~GPIO_IOCTL_BV(pin);\
} while(0)

// GPIO输出模式
#define GPIO_Mode_Output(port,pin) do{\
P##port##DIR |= GPIO_IOCTL_BV(pin);\
} while(0)
    
// GPIO输入状态
#define GPIO_Input_Mode(port,pin,var) do{\
if(var == 0){\
  P##port##INP &= ~GPIO_IOCTL_BV(pin);\
}else{\
  P##port##INP |= GPIO_IOCTL_BV(pin);\
}\
} while(0)

// GPIO配置输入
// P1_0, P1_1 不能用作输入
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
