/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Mar 23, 2025
 *      Author: ASUS
 */

#include "stm32f407xx_spi_driver.h"

/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- March 26, 2025
 *
 *  @fn						- SPI_PeriClockControl
 *
 *  @brief					- This function enables or disables peripheral clock for given SPIx peripheral
 *
 *	@param[in]				- Base address of the SPIx peripheral
 *	@param[in]				- ENABLE or DISABLE macros
 *	@param[in]				-
 *
 *	@return					- None
 *
 *	@Note					- None
 *
 */
void
SPI_PeriClockControl(SPI_RegDef_t* pSPIx, uint8_t u8EnOrDi)
{
	if (ENABLE == u8EnOrDi)
	{
		if (pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if (pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if (pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else
	{
		if (pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if (pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if (pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}



/*****************************************************************************************************
 * 	@author					- Ngo Kien Hoang (hoang.ngo000187@gmail.com)
 * 	@day					- March 26, 2025
 *
 *  @fn						- SPI_Init
 *
 *  @brief					- This function enables or disables peripheral clock for given SPIx peripheral
 *
 *	@param[in]				- Base address of the SPI peripheral
 *	@param[in]				- ENABLE or DISABLE macros
 *	@param[in]				-
 *
 *	@return					- None
 *
 *	@Note					- None
 *
 */
void
SPI_Init(SPI_Handle_t *pSPIHandle)
{

}
