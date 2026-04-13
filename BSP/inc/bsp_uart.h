#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "bsp_gpio.h"

#define STM32F10X_MD 1
#include "stm32f10x.h"
/*
定义一个初始化配置结构体
*/
// typedef enum
// {
//     BSP_UART_1 = 0,
//     BSP_UART_2,
//     BSP_UART_3,
// } bsp_uart_id_t;

typedef struct
{
    const bsp_gpio_t *tx;
    const bsp_gpio_t *rx;
} bsp_uart_io_t;

/*
因为这里的 tx/rx 通常不是“UART 自己拥有的一份 GPIO 对象”，而是：
UART 只是引用“板级已经定义好的 GPIO 资源”。
所以才常写成指针。
你先看两种写法的本质区别。
*/

/*

因为 io 只是 bsp_uart_t 的一个小子结构体，用来归类 tx/rx 这两个成员。
它本身很小，只有两个指针：
const bsp_gpio_t *tx;
const bsp_gpio_t *rx;
这种情况下，直接内嵌最自然：
bsp_uart_io_t io;
这样访问也清楚：
uart->io.tx
uart->io.rx
如果你再多套一层指针：
bsp_uart_io_t *io;
那你还得额外分配/定义一个 io 对象，再让 uart 去指向它，没什么必要，反而更绕。
*/

typedef struct
{
    USART_TypeDef     *instance; // USART1 / USART2 / USART3
    IRQn_Type         irqn;
    bsp_uart_io_t     io;
    USART_InitTypeDef init_cfg;
    uint32_t          baudrate;
} bsp_uart_t;

/*
但还差一个最关键字段：USART 实例本身
因为你后面真正调用 STM32 标准库时，最常用的是这个东西：
USART_Init(USART1, &uart_init);
USART_SendData(USART1, data);
USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
USART_Cmd(USART1, ENABLE);
这些函数真正需要的是

USART1 / USART2 / USART3 这种外设实例指针

而不是：

BSP_UART_1
BSP_UART_2
那你后面每次都得写 switch：

switch (uart->uart_id)
{
case BSP_UART_1:
    USART_Init(USART1, &uart_init);
    break;
case BSP_UART_2:
    USART_Init(USART2, &uart_init);
    break;
case BSP_UART_3:
    USART_Init(USART3, &uart_init);
    break;
}
*/

//但从语义上看，init 函数只是读取配置，不会修改 uart 这个配置对象本身。
void bsp_uart_init(bsp_uart_t *uart);
void bsp_uart_send_byte(bsp_uart_t *uart, uint8_t data);
void bsp_uart_send_buf(bsp_uart_t *uart, const uint8_t *buf, uint32_t len);
void bsp_uart_send_string(bsp_uart_t *uart, const char *str);

#endif
