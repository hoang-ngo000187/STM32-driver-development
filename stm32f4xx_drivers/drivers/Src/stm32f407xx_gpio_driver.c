/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Jul 23, 2024
 *      Author: ASUS
 */

#include "stm32f407xx_gpio_driver.h"

/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- Jul 24, 2024
 *
 *  @fn						- GPIO_PeriClockControl
 *
 *  @brief					- This function enables or disables peripheral clock for given GPIO port
 *
 *	@param[in]				- Base address of the GPIO peripheral
 *	@param[in]				- ENABLE or DISABLE macros
 *	@param[in]				-
 *
 *	@return					- None
 *
 *	@Note					- None
 *
 */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t u8EnOrDi)
{
	if (ENABLE == u8EnOrDi)
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
		else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}
}



/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- Jul 24, 2024
 *
 *  @fn						- GPIO_Init
 *
 *  @brief					- This function enables or disables peripheral clock for given GPIO port
 *
 *	@param[in]				- Base address of the GPIO peripheral
 *	@param[in]				- ENABLE or DISABLE macros
 *	@param[in]				-
 *
 *	@return					- None
 *
 *	@Note					- None
 *
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t u32temp = 0;

	/*!< 01. Configure the mode of GPIO pin >*/
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		/* Non-Interrupt mode */
		u32temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));	// Clearing
		pGPIOHandle->pGPIOx->MODER |= u32temp;	// Setting
	}
	else
	{
		/* Interrupt mode */
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FALLING_EDGE_TRIGGER)
		{
			/* 01. Config the FTSR */
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			/* Clear the corresponding RTSR bit */
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RISING_EDGE_TRIGGER)
		{
			/* 01. Config the RTSR */
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			/* Clear the corresponding FTSR bit */
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FALLING_RISING_EDGE_TRIGGER)
		{
			/* 01. Config both the RTSR and FTSR */
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		/* 02. Config the GPIO Port selection in SYSCFG_EXTICR */
		uint8_t u8temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t u8temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t u8portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[u8temp1] |= (u8portcode << (u8temp2 * 4));

		/* 03. Enable EXTI interrupt delivery using IMR (Interrupt mask register) */
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	u32temp = 0;

	/*!< 02. Configure the speed >*/
	u32temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));	// Clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= u32temp;	// Setting

	u32temp = 0;

	/*!< 03. Configure the pull-up/pull-down settings >*/
	u32temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));	// Clearing
	pGPIOHandle->pGPIOx->PUPDR |= u32temp;	// Setting

	u32temp = 0;

	/*!< 04. Configure the output type >*/
	u32temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));	// Clearing
	pGPIOHandle->pGPIOx->OTYPER |= u32temp;	// Setting

	u32temp = 0;

	/*!< 05. Configure the alternate functionality >*/
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t u8temp1 = 0;
		uint8_t u8temp2 = 0;

		u8temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8);
		u8temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8);

		u32temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFuncMode << (4 * u8temp2));
		pGPIOHandle->pGPIOx->AFR[u8temp1] &= ~(0xF << (4 * u8temp2));	// Clearing
		pGPIOHandle->pGPIOx->AFR[u8temp1] |= u32temp;	// Setting
	}
}

void GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
{
	if (pGPIOx == GPIOA)
	{
		GPIOA_PCLK_EN();
	}
	else if (pGPIOx == GPIOB)
	{
		GPIOB_PCLK_EN();
	}
	else if (pGPIOx == GPIOC)
	{
		GPIOC_PCLK_EN();
	}
	else if (pGPIOx == GPIOD)
	{
		GPIOD_PCLK_EN();
	}
	else if (pGPIOx == GPIOE)
	{
		GPIOE_PCLK_EN();
	}
	else if (pGPIOx == GPIOF)
	{
		GPIOF_PCLK_EN();
	}
	else if (pGPIOx == GPIOG)
	{
		GPIOG_PCLK_EN();
	}
	else if (pGPIOx == GPIOH)
	{
		GPIOH_PCLK_EN();
	}
	else if (pGPIOx == GPIOI)
	{
		GPIOI_PCLK_EN();
	}
}



/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- Jul 28, 2024
 *
 *  @fn						- GPIO_ReadFromInputPin
 *
 *  @brief					- This function to read the state of GPIO Input pin
 *
 *	@param[in]				- Base address of the GPIO peripheral
 *	@param[in]				- Pin number
 *	@param[in]				-
 *
 *	@return					- 0 or 1
 *
 *	@Note					- None
 *
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t u8PinNumber)
{
	uint8_t u8Value = 0;
	u8Value = (uint8_t)((pGPIOx->IDR >> u8PinNumber) & 0x00000001);
	return u8Value;
}

/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- Jul 28, 2024
 *
 *  @fn						- GPIO_ReadFromInputPort
 *
 *  @brief					- This function to read the state of GPIO Input port
 *
 *	@param[in]				- Base address of the GPIO peripheral
 *	@param[in]				-
 *	@param[in]				-
 *
 *	@return					- u16Value
 *
 *	@Note					- None
 *
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t u16Value = 0;
	u16Value = (uint16_t)(pGPIOx->IDR);
	return u16Value;
}

/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- Jul 28, 2024
 *
 *  @fn						- GPIO_WriteToOutputPin
 *
 *  @brief					- This function to write the value to GPIO Output pin
 *
 *	@param[in]				- Base address of the GPIO peripheral
 *	@param[in]				- Pin number
 *	@param[in]				- Value
 *
 *	@return					- void
 *
 *	@Note					- None
 *
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t u8PinNumber, uint8_t u8Value)
{
	if (u8Value == GPIO_PIN_SET)
	{
		// Write 1 to the Output data register at the bit field corresponding pin number
		pGPIOx->ODR |= (1 << u8PinNumber);
	}
	else
	{
		// Write 0 to the Output data register at the bit field corresponding pin number
		pGPIOx->ODR &= ~(1 << u8PinNumber);
	}
}

/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- Jul 28, 2024
 *
 *  @fn						- GPIO_WriteToOutputPort
 *
 *  @brief					- This function to write the value to GPIO Output port
 *
 *	@param[in]				- Base address of the GPIO peripheral
 *	@param[in]				- u16Value
 *	@param[in]				-
 *
 *	@return					- void
 *
 *	@Note					- None
 *
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t u16Value)
{
	pGPIOx->ODR = u16Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t u8PinNumber)
{
	pGPIOx->ODR ^= (1 << u8PinNumber);
}



/*!< IRQ Configuration and ISR handling >*/
void GPIO_IRQInterruptConfig(uint8_t u8IRQNumber, uint8_t u8EnOrDi)
{
	if (u8EnOrDi == ENABLE)
	{
		if (u8IRQNumber <= 31)
		{
			// Program ISER0 register
			*NVIC_ISER0 |= (1 << u8IRQNumber);
		}
		else if (u8IRQNumber > 31 && u8IRQNumber < 64)
		{
			// Program ISER1 register
			*NVIC_ISER1 |= (1 << (u8IRQNumber % 32));
		}
		else if (u8IRQNumber >= 64 && u8IRQNumber < 96)
		{
			// Program ISER2 register
			*NVIC_ISER2 |= (1 << (u8IRQNumber % 64));
		}
	}
	else
	{
		if (u8IRQNumber <= 31)
		{
			// Program ICER0 register
			*NVIC_ICER0 |= (1 << u8IRQNumber);
		}
		else if (u8IRQNumber > 31 && u8IRQNumber < 64)
		{
			// Program ICER1 register
			*NVIC_ICER1 |= (1 << (u8IRQNumber % 32));
		}
		else if (u8IRQNumber >= 64 && u8IRQNumber < 96)
		{
			// Program ICER2 register
			*NVIC_ICER1 |= (1 << (u8IRQNumber % 64));
		}
	}
}

void GPIO_IRQPriorityConfig(uint8_t u8IRQNumber, uint8_t u8IRQPriority)
{
	uint8_t u8Iprx = u8IRQNumber/4;
	uint8_t u8Iprx_section = u8IRQNumber%4;

	uint8_t u8Bitshift = (8 * u8Iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASEADDR + (u8Iprx*4)) |= (u8IRQPriority << u8Bitshift);
}

void GPIO_IRQHandling(uint8_t u8PinNumber)
{
	// Clear the EXTI PR Register corresponding to the Pin number
	if (EXTI->PR & (1 << u8PinNumber))
	{
		// Clear
		EXTI->PR |= (1 << u8PinNumber);
	}
}

