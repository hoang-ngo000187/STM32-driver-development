/*
 * stm32f407xx.h
 *
 *  Created on: Jul 14, 2024
 *      Author: NGO KIEN HOANG (hoang.ngo000187@gmail.com)
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo	volatile


/************************************************************* START - PROCESSOR SPECIFIC DETAILS ****************************************************/
/* Check Cortex -M4 Devices Generic User Guide file for more details */

/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0						( (__vo uint32_t *)0xE000E100 )
#define NVIC_ISER1						( (__vo uint32_t *)0xE000E104 )
#define NVIC_ISER2						( (__vo uint32_t *)0xE000E108 )
#define NVIC_ISER3						( (__vo uint32_t *)0xE000E10C )

/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0						( (__vo uint32_t *)0xE000E180 )
#define NVIC_ICER1						( (__vo uint32_t *)0xE000E184 )
#define NVIC_ICER2						( (__vo uint32_t *)0xE000E188 )
#define NVIC_ICER3						( (__vo uint32_t *)0xE000E18C )

/*
 * ARM Cortex Mx Processor NVIC IPR register Base Addresses
 */
#define NVIC_IPR_BASEADDR				( (__vo uint32_t *)0xE000E400 )

#define NO_PR_BITS_IMPLEMENTED			4
/************************************************************** END - PROCESSOR SPECIFIC DETAILS *****************************************************/


/*
 * BASE ADDRESSES OF FLASH AND SRAM MEMORIES
 */
#define FLASH_BASEADDR					0x08000000U
#define SRAM1_BASEADDR					0x20000000U		// 112KB
#define SRAM2_BASEADDR					0x2001C000U		// 16KB
#define ROM_BASEADDR					0x1FFF0000U
#define SRAM							SRAM1_BASEADDR

/*
 * BASE ADDRESSES OF AHBx and APBx Peripheral
 */
#define PERIPH_BASE						0x40000000U
#define APB1PERIPH_BASEADDR				PERIPH_BASE
#define APB2PERIPH_BASEADDR				0x40010000U
#define AHB1PERIPH_BASEADDR				0x40020000U
#define AHB2PERIPH_BASEADDR				0x50000000U

/*
 * BASE ADDRESSES OF PERIPHERAL WHICH ARE HANGING ON AHB1 BUS
 * TODO: COMPLETE FOR ALL OTHER PERIPHERALS
 */
#define GPIOA_BASEADDR					(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR					(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR					(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR					(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR					(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR					(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR					(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR					(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR					(AHB1PERIPH_BASEADDR + 0x2000)

#define RCC_BASEADDR					(AHB1PERIPH_BASEADDR + 0x3800)

/*
 * BASE ADDRESSES OF PERIPHERAL WHICH ARE HANGING ON APB1 BUS
 * TODO: COMPLETE FOR ALL OTHER PERIPHERALS
 */
#define I2C1_BASEADDR					(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR					(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR					(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR					(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR					(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR					(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR					(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR					(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR					(APB1PERIPH_BASEADDR + 0x5000)

/*
 * BASE ADDRESSES OF PERIPHERAL WHICH ARE HANGING ON APB2 BUS
 * TODO: COMPLETE FOR ALL OTHER PERIPHERALS
 */
#define EXTI_BASEADDR					(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR					(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR					(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR					(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR					(APB2PERIPH_BASEADDR + 0x1400)


/************************************************************* PERIPHERAL REGISTER DEFINITION STRUCTURES ****************************************************/

/*
 * PERIPHERAL REGISTER DEFINITIONS STRUCTURE FOR GPIO
 */
typedef struct
{
	__vo uint32_t MODER;		/* GPIO port mode register										;	Address offset: 0x00 */
	__vo uint32_t OTYPER;		/* GPIO port output type register								;	Address offset: 0x04 */
	__vo uint32_t OSPEEDR;		/* GPIO port output speed register 								;	Address offset: 0x08 */
	__vo uint32_t PUPDR;		/* GPIO port pull-up/pull-down register							;	Address offset: 0x0C */
	__vo uint32_t IDR;			/* GPIO port input data register								;	Address offset: 0x10 */
	__vo uint32_t ODR;			/* GPIO port output data register 								;	Address offset: 0x14 */
	__vo uint32_t BSRR;			/* GPIO port bit set/reset register								;	Address offset: 0x18 */
	__vo uint32_t LCKR;			/* GPIO port configuration lock register						;	Address offset: 0x1C */
	__vo uint32_t AFR[2];		/* GPIO alternate function low (AFR[0]) / high (AFR[1] register	;	Address offset: 0x20/0x24 */
} GPIO_RegDef_t;

/*
 * PERIPHERAL REGISTER DEFINITIONS STRUCTURE FOR RCC
 */
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
		 uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
		 uint32_t RESERVED1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
		 uint32_t RESERVED2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
		 uint32_t RESERVED3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
		 uint32_t RESERVED4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
		 uint32_t RESERVED5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
		 uint32_t RESERVED6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
} RCC_RegDef_t;

/*
 * PERIPHERAL REGISTER DEFINITIONS STRUCTURE FOR EXTI
 */
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
} EXTI_RegDef_t;

/*
 * PERIPHERAL REGISTER DEFINITIONS STRUCTURE FOR SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRM;		// Offset: 0x00
	__vo uint32_t PMC;			// Offset: 0x04
	__vo uint32_t EXTICR[4];	// Offset: 0x08 -> 0x14
	__vo uint32_t RESERVED[2];	// 0ffset: 0x18 -> 0x1C
	__vo uint32_t CMPCR;		// Offset: 0x20
} SYSCFG_RegDef_t;



/*
 * PERIPHERAL DEFINITIONS (Peripheral base address typecasted to xxx_RegDef_t)
 */
#define GPIOA	((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB	((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC	((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD	((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE	((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF	((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG	((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH	((GPIO_RegDef_t*) GPIOH_BASEADDR)
#define GPIOI	((GPIO_RegDef_t*) GPIOI_BASEADDR)

#define RCC		((RCC_RegDef_t*) RCC_BASEADDR)

#define EXTI	((EXTI_RegDef_t*) EXTI_BASEADDR)

#define SYSCFG	((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 0))
#define GPIOB_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 1))
#define GPIOC_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 2))
#define GPIOD_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 3))
#define GPIOE_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 4))
#define GPIOF_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 5))
#define GPIOG_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 6))
#define GPIOH_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 7))
#define GPIOI_PCLK_EN()	(RCC->AHB1ENR |= (0x0001 << 8))

/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()	(RCC->APB1ENR |= (0x0001 << 21))

/*
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()	(RCC->APB2ENR |= (0x0001 << 12))

/*
 * Clock Enable Macros for USARTx peripherals
 */

/*
 * Clock Enable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (0x0001 << 14))


/*
 * Clock Disable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 0))
#define GPIOB_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 1))
#define GPIOC_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 2))
#define GPIOD_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 3))
#define GPIOE_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 4))
#define GPIOF_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 5))
#define GPIOG_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 6))
#define GPIOH_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 7))
#define GPIOI_PCLK_DI()	(RCC->AHB1ENR &= ~(0x0001 << 8))



/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 0)); (RCC->AHB1RSTR &= ~(0x0001 << 0)); } while (0)
#define GPIOB_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 1)); (RCC->AHB1RSTR &= ~(0x0001 << 1)); } while (0)
#define GPIOC_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 2)); (RCC->AHB1RSTR &= ~(0x0001 << 2)); } while (0)
#define GPIOD_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 3)); (RCC->AHB1RSTR &= ~(0x0001 << 3)); } while (0)
#define GPIOE_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 4)); (RCC->AHB1RSTR &= ~(0x0001 << 4)); } while (0)
#define GPIOF_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 5)); (RCC->AHB1RSTR &= ~(0x0001 << 5)); } while (0)
#define GPIOG_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 6)); (RCC->AHB1RSTR &= ~(0x0001 << 6)); } while (0)
#define GPIOH_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 7)); (RCC->AHB1RSTR &= ~(0x0001 << 7)); } while (0)
#define GPIOI_REG_RESET()	do { (RCC->AHB1RSTR |= (0x0001 << 8)); (RCC->AHB1RSTR &= ~(0x0001 << 8)); } while (0)


/*
 * Return port code for given GPIOx base address
 */
#define GPIO_BASEADDR_TO_CODE(x)	((x == GPIOA)? 0 :\
										(x == GPIOB)? 1 :\
												(x == GPIOC)? 2 :\
													(x == GPIOD)? 3 :\
															(x == GPIOE)? 4 :\
																	(x == GPIOF)? 5 :\
																			(x == GPIOG)? 6 :\
																					(x == GPIOH)? 7 : 0)




/*
 * IRQ (Interrupt Request) Numbers of STM32F407x MCU
 * NOTE: update these macros with valid values according to your MCU
 * TODO: You may complete this list for other peripherals
 */
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40



/*********************************************************************** SOME GENERIC MACROS **************************************************************/

#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#include "stm32f407xx_gpio_driver.h"

#endif /* INC_STM32F407XX_H_ */
