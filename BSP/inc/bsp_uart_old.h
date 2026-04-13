#if 0

#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "bsp_gpio.h"

/*
定义一个初始化配置结构体
*/
typedef enum
{
    BSP_UART_1 = 0,
    BSP_UART_2,
    BSP_UART_3,
} bsp_uart_id_t;

typedef struct
{
    const bsp_gpio_t *tx;
    const bsp_gpio_t *rx;
} bsp_uart_pin_t;


typedef struct
{
    bsp_uart_id_t   uart_id;
    bsp_uart_pin_t  pin;
    uint32_t        baudrate;
    // uint16_t       irq_handler; // 先写成 uint16_t，后续再改成函数指针
    //中断号
    //回调函数
} bsp_uart_init_t;


//这样不是资源+配置，不好用

// 版本 B：更工程化一点

// 把硬件资源也放进来。

// typedef struct
// {
//     bsp_uart_id_t      *instance;
//     uint32_t            uart_clk;
//     IRQn_Type           irqn;
//     const bsp_gpio_t   *tx;
//     const bsp_gpio_t   *rx;
//     uint32_t            baudrate;
// } bsp_uart_init_t;



/*初始化*/
void bsp_uart_init(const bsp_uart_init_t *cfg);
/*写*/

// 第一版必须有
// bsp_uart_init()
// bsp_uart_send_byte()
// bsp_uart_send_buf()
// bsp_uart_send_string()
// 第二版再加
// bsp_uart_read_byte() 或接收接口
// bsp_uart_irq_handler()
// 接收中断支持
// 第三版再加
// 环形缓冲
// printf 重定向
// 多串口支持
// DMA 发送/接收

// 你现在先把第一版 + 中断接收雏形写好，就够了。

#endif // !__BSP_UART_H
#endif