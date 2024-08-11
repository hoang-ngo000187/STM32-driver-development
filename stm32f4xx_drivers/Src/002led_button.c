/*
 * 002led_button.c
 *
 *  Created on: Aug 3, 2024
 *      Author: ASUS
 */
#include "stm32f407xx.h"

#define HIGH	1

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed;
	GPIO_Handle_t GpioBtn;

	/*!< Initialize GPIO Pin LED (PD12) >*/
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_TYPE_PUSHPULL;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PULL_UP;
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);

	/*!< Initialize GPIO Pin Button (PA0) >*/
	GpioBtn.pGPIOx = GPIOA;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PULL_UP_PULL_DOWN;
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&GpioBtn);

	while (1)
	{
		if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == GPIO_PIN_HIGH)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		}
	}

	return 0;
}

void EXTI0_IRQHandler(void)
{
	GPIO_IRQHandling(0);
}
