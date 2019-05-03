/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "project.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED_OFF() GPIO_SetBits(GPIOC, GPIO_Pin_13)        //端口置1
#define LED_ON() GPIO_ResetBits(GPIOC, GPIO_Pin_13)     //端口置0

// use for dust sensor; uart2 pa2 pa3 9600
UART *dust_uart;
GA6* ga6;
char dust_buffer[9];
float dust_value;
char uart_msg[20];

void long_delay(uint16_t k)
{
	int i;
	for (i = 0; i < k; i ++) {
		DELAY_MS(1000);
	}
}

int main(void)
{
    uint16_t i = 0;

    SystemInit();
    RCC_Configuration();
    init_led();
    LED_OFF();
    delay_init();
    memset(dust_buffer,0,9);
    long_delay(20);
    LED_ON();
    ga6 = ga6_new_dev();

    long_delay(2);
    ga6->init(ga6);


    dust_uart = uart_new_dev(UART_ID_2, 9600);
    for(;;) {

    	if ( dust_uart->msg.ring_io->master->get_current_size(dust_uart->msg.ring_io) >= 9) {
    		dust_uart->msg.ring_io->master->pop(dust_uart->msg.ring_io, dust_buffer, 9);
    		if (dust_buffer[0] == 0xFF) {
    			dust_value = dust_buffer[3]  + dust_buffer[4]*0.001;
    			sprintf(uart_msg, "#%3.3f#", dust_value);
    			ga6->socket_send(ga6, uart_msg, -1);
    		}
    	}

    }

}


void init_led()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能GPIOD的时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;                    //指定引脚13
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //设置输出速率50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出模式
    GPIO_Init(GPIOC, &GPIO_InitStructure);                            //初始化外设GPIOx寄存
}

void RCC_Configuration(void)
{
    /* Enable system clocks ------------------------------------------------*/
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();                                                                                   // System clock reset.
    RCC_HSEConfig( RCC_HSE_ON );                                                                    // Open the HSE clock.
    HSEStartUpStatus = RCC_WaitForHSEStartUp();                                                     // Wait for HSE clock.
#if 1
    if( HSEStartUpStatus == SUCCESS ) {                                                             // If the HSE time consuming normal.

        FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable );                                     // Enable flash reader buffer.
        FLASH_SetLatency( FLASH_Latency_2 );                                                        // Flash wait state.
        RCC_HCLKConfig( RCC_SYSCLK_Div1 );                                                          // HCLK = SYSCLK = 72.0MHz
        RCC_PCLK2Config( RCC_HCLK_Div1 );                                                           // PCLK2 = HCLK = 72.0MHz
        RCC_PCLK1Config( RCC_HCLK_Div2 );                                                           // PCLK1 = HCLK/2 = 36.0MHz

        RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);                                                                         // Enable PLL

        while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET );                                       // Wait till PLL is ready.
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );                                                // Select PLL as system clock source.
        while( RCC_GetSYSCLKSource() != 0x08 );                                                     // Wait till PLL is used as system clock source.
    }
    // notice :
    // If there is as "RCC_ADCCLKConfig( RCC_PCLK2_Div6 )" peripheral clock.
    // So, the ADCLK = PCLK2 / 6 = 12MHz.
#endif
    /* Enable peripheral clocks ------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);
    /* Enable DMA1 and DMA2 clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);
    /* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 |
                           RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1   , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOD ,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}
