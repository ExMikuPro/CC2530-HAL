#include "cc2530_hal_GPIO.h"

/* GPIO������� */
#define GPIO_IO_OUTPUT(port, pin) do {\
    GPIO_Type_TY(port,pin);\
    GPIO_Mode_Output(port,pin);\
}while(0)

/* GPIO�������� */
#define GPIO_IO_INPUT_UP(port, pin) do {\
    GPIO_IO_INPUT(port, pin, GPIO_INPUT_PULLUP);\
} while(0)

/* GPIO�������� */
#define GPIO_IO_INPUT_DOWN(port, pin) do {\
    GPIO_IO_INPUT(port, pin, GPIO_INPUT_PULLDOWN);\
} while(0)







