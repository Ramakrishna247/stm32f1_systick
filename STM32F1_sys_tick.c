#include<stm32f10x.h>

void SysTick_Initialize(uint32_t ticks){

	
SysTick->CTRL =0;
	SysTick->LOAD =ticks-1;
	NVIC_SetPriority(SysTick_IRQn,-1);
	SysTick->VAL=0;
	SysTick->CTRL &=~SysTick_CTRL_CLKSOURCE;
	SysTick->CTRL |=SysTick_CTRL_TICKINT;
	SysTick->CTRL |=SysTick_CTRL_ENABLE;

}

unsigned int Timer;

void SysTick_Handler (void)
{

	Timer++;	/* Increment performance counter */

	
	
}


void delay(unsigned int);


int main(void)
{

uint32_t tick=1000;
SysTick_Initialize(tick);
	
RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	
GPIOC->CRH &=~GPIO_CRH_CNF13_0;	
GPIOC->CRH &=~GPIO_CRH_CNF13_1;
	
GPIOC->CRH |=GPIO_CRH_MODE13_0;
GPIOC->CRH &=~GPIO_CRH_MODE13_1;

while(1)
{	

	
GPIOC->BSRR |=GPIO_BSRR_BR13;
delay(1000);	
GPIOC->BSRR |=GPIO_BSRR_BS13;
delay(1000);	
}

}


void delay(unsigned int x)
{

unsigned z;
	
	z=Timer;
	
	while(!((Timer-z)>=x))
	{}

		return;

}