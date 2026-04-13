#include "bsp_gpio.h"


/*初始化*/
void bsp_gpio_init(const bsp_gpio_t *gpio, const bsp_gpio_init_t *cfg)
{
    if (cfg==0||gpio ==0)
    {
        return;
    }
    GPIO_InitTypeDef gpio_init;
    RCC_APB2PeriphClockCmd(gpio->clk, ENABLE);
    gpio_init.GPIO_Pin   = gpio->pin;
    gpio_init.GPIO_Mode  = cfg->mode;
    gpio_init.GPIO_Speed = cfg->speed;
    GPIO_Init(gpio->port, &gpio_init);
}
/*写引脚*/
void bsp_gpio_write(const bsp_gpio_t *gpio, uint8_t level)
{
    if (gpio ==0)
    {
        return;
    }
    if (level)
    {
        GPIO_SetBits(gpio->port, gpio->pin);
    }
    else
    {
        GPIO_ResetBits(gpio->port, gpio->pin);
    }
}
/*读引脚*/
uint8_t bsp_read_gpio(const bsp_gpio_t *gpio)
{
    if (gpio ==0)
    {
        //return -1;
    }
    return GPIO_ReadInputDataBit(gpio->port, gpio->pin);

}
/*翻转引脚*/
void bsp_gpio_toggle(const bsp_gpio_t *gpio)
{
    if (gpio == 0)
    {
        return;
    }
    if (GPIO_ReadInputDataBit(gpio->port, gpio->pin))
    {
        GPIO_ResetBits(gpio->port, gpio->pin);
    }
    else
    {
        GPIO_SetBits(gpio->port, gpio->pin);
    }

}
/*可选：单独时钟使能*/
/*这里知识APB2的时钟，还缺少其他时钟*/
void bsp_gpio_clk_enable(uint32_t clk)
{
    if (clk == 0)
    {
        RCC_APB2PeriphClockCmd(clk, ENABLE);
    }
    
}

