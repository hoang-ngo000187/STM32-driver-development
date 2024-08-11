/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Jul 23, 2024
 *      Author: ASUS
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;				/*!< Possible value from @GPIO_PIN_NUMBERS >*/
	uint8_t GPIO_PinMode;				/*!< Possible value from @GPIO_PIN_MDOES >*/
	uint8_t GPIO_PinSpeed;				/*!< Possible value from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdControl;		/*!< Possible value from @GPIO_PIN_PUPD >*/
	uint8_t GPIO_PinOPType;				/*!< Possible value from @GPIO_PIN_OP_TYPES >*/
	uint8_t GPIO_PinAltFuncMode;
} GPIO_PinConfig_t;

/*
 * This is a Handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx; 				/*!< This holds the base address of the GPIO port to which the pin belongs >*/
	GPIO_PinConfig_t GPIO_PinConfig;	/*!< This holds GPIO pin configuration settings >*/

} GPIO_Handle_t;



/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0								0
#define GPIO_PIN_NO_1								1
#define GPIO_PIN_NO_2								2
#define GPIO_PIN_NO_3								3
#define GPIO_PIN_NO_4								4
#define GPIO_PIN_NO_5								5
#define GPIO_PIN_NO_6								6
#define GPIO_PIN_NO_7								7
#define GPIO_PIN_NO_8								8
#define GPIO_PIN_NO_9								9
#define GPIO_PIN_NO_10								10
#define GPIO_PIN_NO_11								11
#define GPIO_PIN_NO_12								12
#define GPIO_PIN_NO_13								13
#define GPIO_PIN_NO_14								14
#define GPIO_PIN_NO_15								15



/*
 * @GPIO_PIN_MDOES
 * GPIO pin possible modes
 */
#define GPIO_MODE_INPUT								0
#define GPIO_MODE_OUTPUT							1
#define GPIO_MODE_ALTFN								2
#define GPIO_MODE_ANALOG							3
#define GPIO_MODE_IT_FALLING_EDGE_TRIGGER			4
#define GPIO_MODE_IT_RISING_EDGE_TRIGGER			5
#define GPIO_MODE_IT_FALLING_RISING_EDGE_TRIGGER	6



/*
 * @GPIO_PIN_OP_TYPES
 * GPIO pin possible output types
 */
#define GPIO_OUTPUT_TYPE_PUSHPULL					0
#define GPIO_OUTPUT_TYPE_OPENDRAIN					1



/*
 * @GPIO_PIN_SPEED
 * GPIO pin possible output speeds
 */
#define GPIO_SPEED_LOW								0 /* 2MHz */
#define GPIO_SPEED_MEDIUM							1 /* 25MHz */
#define GPIO_SPEED_FAST								2 /* 50MHz */
#define GPIO_SPEED_HIGH								3 /* 100MHz */



/*
 * @GPIO_PIN_PUPD
 * GPIO pin Pull-up/Pull-down configuration macros
 */
#define GPIO_PIN_NO_PULL_UP_PULL_DOWN						0
#define GPIO_PIN_PULL_UP									1
#define GPIO_PIN_PULL_DOWN									2



/*
 * GPIO state: HIGH / LOW
 */
#define GPIO_PIN_HIGH	1
#define GPIO_PIN_LOW	0

/********************************************************************************************************************
 *												APIs supported by GPIO driver
 *							For more information about the APIs, check the function definitions
 ********************************************************************************************************************/
/*!< Peripheral clock control >*/
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t u8EnOrDi);

/*!< Init and De-init >*/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);

/*!< Data Read/Write >*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t u8PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t u8PinNumber, uint8_t u8Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t u16Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t u8PinNumber);

/*!< IRQ Configuration and ISR handling >*/
void GPIO_IRQInterruptConfig(uint8_t u8IRQNumber, uint8_t u8EnOrDi);
void GPIO_IRQPriorityConfig(uint8_t u8IRQNumber, uint8_t u8IRQPriority);
void GPIO_IRQHandling(uint8_t u8PinNumber);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
