#include "bsp_gpio.h"
static const bsp_gpio_t led_gpio = {
    .port = GPIOC,
    .pin  = GPIO_Pin_13,
    .clk  = RCC_APB2Periph_GPIOC
};

static const bsp_gpio_init_t led_gpio_init_cfg = {
    .mode  = GPIO_Mode_Out_PP,
    .speed = GPIO_Speed_50MHz,
};

void bsp_led_init(void)
{
    bsp_gpio_init(&led_gpio, &led_gpio_init_cfg);
}

void bsp_led_on(void)
{
    bsp_gpio_write(&led_gpio, 0);   // 假设低电平点亮
}

void bsp_led_off(void)
{
    bsp_gpio_write(&led_gpio, 1);
}

void bsp_led_toggle(void)
{
    bsp_gpio_toggle(&led_gpio);
}


