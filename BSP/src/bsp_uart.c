#include "bsp_uart.h"

static const bsp_gpio_t g_uart1_tx = {
    .port = GPIOA,
    .pin  = GPIO_Pin_9,
    .clk  = RCC_APB2Periph_GPIOA,
};

static const bsp_gpio_t g_uart1_rx = {
    .port = GPIOA,
    .pin  = GPIO_Pin_10,
    .clk  = RCC_APB2Periph_GPIOA,
};

static const bsp_gpio_init_t uart1_tx_init_cfg = {
    .mode  = GPIO_Mode_AF_PP,
    .speed = GPIO_Speed_50MHz,
};

static const bsp_gpio_init_t uart1_rx_init_cfg = {
    .mode  = GPIO_Mode_IPU,
    .speed = GPIO_Speed_50MHz,
};



bsp_uart_io_t io = {
    .tx = &g_uart1_tx,
    .rx = &g_uart1_rx,
};
//这就是“引用外部资源”
//USART1_IRQn   37
const bsp_uart_t g_uart1 = {
    .instance = USART1,
    .irqn     = 37,
    .init_cfg = {
                .USART_BaudRate = 115200,
                .USART_HardwareFlowControl  = USART_HardwareFlowControl_None,//硬件流控制，不需要
                .USART_Mode                 = USART_Mode_Tx,                //模式，选择为发送模式
                .USART_Parity               = USART_Parity_No,              //奇偶校验，不需要
                .USART_StopBits             = USART_StopBits_1,             //停止位，选择1位
                .USART_WordLength           = USART_WordLength_8b,          //字长，选择8位
                },
    .io =      {
                .tx = &g_uart1_tx,
                .rx = &g_uart1_rx,
                },
};

void bsp_uart_init(bsp_uart_t *uart)
{
    if (uart==0)
    {
        return;
    }
    
    /*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	
    /*GPIO初始化*/
	bsp_gpio_init(&uart->io.tx,&uart1_tx_init_cfg);
    bsp_gpio_init(&uart->io.rx,&uart1_rx_init_cfg);
    
    /*USART初始化*/
    USART_Init(uart->instance, &uart->init_cfg);				//将结构体变量交给USART_Init，配置USART1
    /*中断输出配置*/
    USART_ITConfig(uart->instance, USART_IT_RXNE, ENABLE);	

    /*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

    /*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;					//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//选择配置NVIC的USART1线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);							//将结构体变量交给NVIC_Init，配置NVIC外设
	
	/*USART使能*/
	USART_Cmd(uart->instance, ENABLE);		
}



void bsp_uart_send_byte(bsp_uart_t *uart, uint8_t byte)
{
    USART_SendData(uart->instance, byte);		//将字节数据写入数据寄存器，写入后USART自动生成时序波形
    while (USART_GetFlagStatus(uart->instance,USART_FLAG_TXE == RESET));//等待发送完成
    /*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
    
}
void bsp_uart_send_buf(bsp_uart_t *uart, const uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        bsp_uart_send_byte(uart, buf[i]);
    }
}
/**
  * 函    数：串口发送一个字符串
  * 参    数：String 要发送字符串的首地址
  * 返 回 值：无
  */
void bsp_uart_send_string(bsp_uart_t *uart, const char *str)
{
    uint32_t len = strlen(str);
    bsp_uart_send_buf(uart, (const uint8_t *)str, len);
}

void bsp_uart_send_number(bsp_uart_t *uart, uint8_t num)
{
    char buf[4]; // 3 位数字 + '\0'
    int len = 0;

    if(num >= 100) {
        buf[len++] = '0' + num / 100;
        num %= 100;
        buf[len++] = '0' + num / 10;
        num %= 10;
        buf[len++] = '0' + num;
    } else if(num >= 10) {
        buf[len++] = '0' + num / 10;
        num %= 10;
        buf[len++] = '0' + num;
    } else {
        buf[len++] = '0' + num;
    }
        buf[len] = '\0';
    bsp_uart_send_string(uart, buf);
}
