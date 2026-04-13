#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_uart.h"
static void delay(volatile uint32_t count)
{
    while (count--)
    {
    }
}

int main(void)
{
    bsp_led_init();
    bsp_uart_init(&g_uart1);
    bsp_uart_send_string(&g_uart1, "Hello, UART!\r\n");

    while (1)
    {
        bsp_led_toggle();
        delay(500000);
    }
}