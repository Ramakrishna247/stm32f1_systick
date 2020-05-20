/*
Author: K.V.Rama Krishna
Project:This program uses systick timer and generates delays on stm32f103c8t6
Date:06.01.2019

*/

#include <stm32f10x.h>


/* ------------ Function to initialize Systick------------------*/

void SysTick_Initialize(unsigned int ticks)
{

	SysTick->CTRL=0; //disable systick timer
	
	SysTick->LOAD =ticks-1; //loads the systick value
	
	NVIC_SetPriority(SysTick_IRQn,(1<<__NVIC_PRIO_BITS)-1); // enable systick interrupt
	
	SysTick->VAL=0;       //make counter current value zero
	
	SysTick->CTRL |=SysTick_CTRL_CLKSOURCE;  //enable clock source , processor clock source is selected as Systick clock source
	
	SysTick->CTRL |=SysTick_CTRL_TICKINT;    // Intialize systick Interrupt bit
	
	SysTick->CTRL |=SysTick_CTRL_ENABLE;    //Enable systick timer

}

volatile int TimeDelay;   

/* ---------------------Systick Handler-------------------*/

void SysTick_Handler(void)
{

if(TimeDelay>0)
  {
   TimeDelay--;
  }
}


/* --------------------Delay Function--------------------*/

void Delay(unsigned int ntime)
{

  TimeDelay=ntime;
	while(TimeDelay !=0);    

}


int main()
{

SysTick_Initialize(100000);

RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;  //initialize GPIO Port c Pin 13 as output
	
GPIOC->CRH &=~GPIO_CRH_CNF13_0;	
GPIOC->CRH &=~GPIO_CRH_CNF13_1;
	
GPIOC->CRH |=GPIO_CRH_MODE13_0;
GPIOC->CRH &=~GPIO_CRH_MODE13_1;	
	

while(1)
{
	
GPIOC->ODR ^=GPIO_ODR_ODR13;   //change led state

Delay(500);     //genereate delay
	
}	
	
}


