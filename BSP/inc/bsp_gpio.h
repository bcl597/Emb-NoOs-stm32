#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f10x.h"
/*
typedef struct
{
    GPIO_TypeDef *port;// GPIO端口
    uint16_t      pin;// GPIO引脚
    uint32_t      clk;// GPIO时钟
    GPIOSpeed_TypeDef speed;// GPIO速度
    GPIOMode_TypeDef mode;// GPIO模式
} bsp_gpio_t;
*/
/*这种写法
“引脚资源信息” 和 “初始化配置” 基本是绑在一起的。
需要把资源和初始化分开才行，资源信息是固定的，而初始化配置是可变的。
*/

/*
定义一个 GPIO 资源结构体
*/
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
    uint32_t      clk;
} bsp_gpio_t;

/*
定义一个初始化配置结构体
*/
typedef struct
{
    // GPIO_TypeDef *port;
    // uint16_t      pin;
    // uint32_t      clk; 不需要重复存储了，直接在初始化函数里用资源结构体的内容就行了。
    GPIOMode_TypeDef mode;
    GPIOSpeed_TypeDef speed;
} bsp_gpio_init_t;

/*初始化*/
void bsp_gpio_init(const bsp_gpio_t *gpio,const bsp_gpio_init_t *cfg);
/*写引脚*/
void bsp_gpio_write(const bsp_gpio_t *gpio, uint8_t level);
/*读引脚*/
uint8_t bsp_read_gpio(const bsp_gpio_t *gpio);
/*翻转引脚*/
void bsp_gpio_toggle(const bsp_gpio_t *gpio);
/*可选：单独时钟使能*/
void bsp_gpio_clk_enable(uint32_t clk);

#endif // !__BSP_GPIO_H
